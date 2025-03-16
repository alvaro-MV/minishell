int
set_or_show_attributes (
     register WORD_LIST *list,
     int attribute,
	 int nodefs
)
{
  register SHELL_VAR *var;
  int assign, undo, any_failed, assign_error, opt;
  int functions_only, arrays_only, assoc_only;
  int aflags;
  char *name;
#if defined (ARRAY_VARS)
  WORD_LIST *nlist, *tlist;
  WORD_DESC *w;
  char optw[8];
  int opti;
#endif

  functions_only = arrays_only = assoc_only = 0;
  undo = any_failed = assign_error = 0;
  /* Read arguments from the front of the list. */
  reset_internal_getopt ();
  while ((opt = internal_getopt (list, ATTROPTS)) != -1)
    {
      switch (opt)
	{
	  case 'n':
	    undo = 1;
	    break;
	  case 'f':
	    functions_only = 1;
	    break;
#if defined (ARRAY_VARS)
	  case 'a':
	    arrays_only = 1;
	    break;
	  case 'A':
	    assoc_only = 1;
	    break;
#endif
	  case 'p':
	    break;
	  CASE_HELPOPT;
	  default:
	    builtin_usage ();
	    return (EX_USAGE);
	}
    }
  list = loptend;

  if (list)
    {
      if (attribute & att_exported)
	array_needs_making = 1;

      /* Cannot undo readonly status, silently disallowed. */
      if (undo && (attribute & att_readonly))
	attribute &= ~att_readonly;

      while (list)
	{
	  name = list->word->word;

	  if (functions_only)		/* xxx -f name */
	    {
	      var = find_function (name);
	      if (var == 0)
		{
		  builtin_error (_("%s: not a function"), name);
		  any_failed++;
		}
	      else if ((attribute & att_exported) && undo == 0 && exportable_function_name (name) == 0)
		{
		  builtin_error (_("%s: cannot export"), name);
		  any_failed++;
		}
	      else
		SETVARATTR (var, attribute, undo);

	      list = list->next;
	      continue;
	    }

	  /* xxx [-np] name[=value] */
	  assign = assignment (name, 0);

	  aflags = 0;
	  if (assign)
	    {
	      name[assign] = '\0';
	      if (name[assign - 1] == '+')
		{
		  aflags |= ASS_APPEND;
		  name[assign - 1] = '\0';
		}
	    }

	  if (legal_identifier (name) == 0)
	    {
	      sh_invalidid (name);
	      if (assign)
		assign_error++;
	      else
		any_failed++;
	      list = list->next;
	      continue;
	    }

	  if (assign)	/* xxx [-np] name=value */
	    {
	      name[assign] = '=';
	      if (aflags & ASS_APPEND)
		name[assign - 1] = '+';
#if defined (ARRAY_VARS)
	      /* Let's try something here.  Turn readonly -a xxx=yyy into
		 declare -ra xxx=yyy and see what that gets us. */
	      if (arrays_only || assoc_only)
		{
		  tlist = list->next;
		  list->next = (WORD_LIST *)NULL;
		  /* Add -g to avoid readonly/export creating local variables:
		     only local/declare/typeset create local variables */
		  opti = 0;
		  optw[opti++] = '-';
		  optw[opti++] = 'g';
		  if (attribute & att_readonly)
		    optw[opti++] = 'r';
		  if (attribute & att_exported)
		    optw[opti++] = 'x';
		  if (arrays_only)
		    optw[opti++] = 'a';
		  else
		    optw[opti++] = 'A';
		  optw[opti] = '\0';

		  w = make_word (optw);
		  nlist = make_word_list (w, list);

		  opt = declare_builtin (nlist);
		  if (opt != EXECUTION_SUCCESS)
		    assign_error++;
		  list->next = tlist;
		  dispose_word (w);
		  free (nlist);
		}
	      else
#endif
	      /* This word has already been expanded once with command
		 and parameter expansion.  Call do_assignment_no_expand (),
		 which does not do command or parameter substitution.  If
		 the assignment is not performed correctly, flag an error. */
	      if (do_assignment_no_expand (name) == 0)
		assign_error++;
	      name[assign] = '\0';
	      if (aflags & ASS_APPEND)
		name[assign - 1] = '\0';
	    }

	  set_var_attribute (name, attribute, undo);
	  if (assign)		/* restore word */
	    {
	      name[assign] = '=';
	      if (aflags & ASS_APPEND)
		name[assign-1] = '+';
	    }
	  list = list->next;
	}
    }
  else
    {
      SHELL_VAR **variable_list;
      register int i;

      if ((attribute & att_function) || functions_only)
	{
	  variable_list = all_shell_functions ();
	  if (attribute != att_function)
	    attribute &= ~att_function;	/* so declare -xf works, for example */
	}
      else
	variable_list = all_shell_variables ();

#if defined (ARRAY_VARS)
      if (attribute & att_array)
	{
	  arrays_only++;
	  if (attribute != att_array)
	    attribute &= ~att_array;
	}
      else if (attribute & att_assoc)
	{
	  assoc_only++;
	  if (attribute != att_assoc)
	    attribute &= ~att_assoc;
	}
#endif

      if (variable_list)
	{
	  for (i = 0; var = variable_list[i]; i++)
	    {
#if defined (ARRAY_VARS)
	      if (arrays_only && array_p (var) == 0)
		continue;
	      else if (assoc_only && assoc_p (var) == 0)
		continue;
#endif

	      /* If we imported a variable that's not a valid identifier, don't
		 show it in any lists. */
	      if ((var->attributes & (att_invisible|att_imported)) == (att_invisible|att_imported))
		continue;

	      if ((var->attributes & attribute))
		{
		  show_var_attributes (var, READONLY_OR_EXPORT, nodefs);
		  if (any_failed = sh_chkwrite (any_failed))
		    break;
		}
	    }
	  free (variable_list);
	}
    }

  return (assign_error ? EX_BADASSIGN
		       : ((any_failed == 0) ? EXECUTION_SUCCESS
  					    : EXECUTION_FAILURE));
}

/* Show all variable variables (v == 1) or functions (v == 0) with
   attributes. */
int
show_all_var_attributes (
     int v,
	 int nodefs
)
{
  SHELL_VAR **variable_list, *var;
  int any_failed;
  register int i;

  variable_list = v ? all_shell_variables () : all_shell_functions ();
  if (variable_list == 0)  
    return (EXECUTION_SUCCESS);

  for (i = any_failed = 0; var = variable_list[i]; i++)
    {
      show_var_attributes (var, READONLY_OR_EXPORT, nodefs);
      if (any_failed = sh_chkwrite (any_failed))
        break;
    }
  free (variable_list);
  return (any_failed == 0 ? EXECUTION_SUCCESS : EXECUTION_FAILURE);
}