import pexpect
import os
import string

# cc -g expand.c  data_structs/dictionary.c data_structs/dictionary2.c tokenizer/tokenizer_utils.c data_structs/dynamic_array.c libft/libft.a

def test_expansion(str):

	print(str)
	expansion = pexpect.spawn(f"../a.out {str}")

	expansion.expect(pexpect.EOF)
	resultado_test = expansion.before
	expected_output = "ooo"
	if resultado_test != expected_output:
		print("Warning: Command output differs from expected output")
		print(f"Expected: {resultado_test}")
		print(f"Actual  : {expected_output.strip()}")

def main():
	test_expansion("$BAR\"ooo\"")
	# test_expansion("$DIS\'PLAY\'")
	# test_expansion("DI$Bar\"\'Hola\"peste")

if ( __name__ == '__main__'):
	main()



# def run_ls_command():
#     try:
#         child = pexpect.spawn('ls')
        
#         child.expect(pexpect.EOF)
        
#         output = child.before #+ child.after
        
#         print(f"Command output: {output.strip()}\n")
        
#         expected_output = "b'expand.c  expansion_test.py'"
#         if output.strip() != expected_output:
#             print("Warning: Command output differs from expected output")
#             print(f"Expected: {expected_output}")
#             print(f"Actual  : {output.strip()}")
    
#     except pexpect.TIMEOUT:
#         print("Command timed out")
#     except Exception as e:
#         print(f"An error occurred: {str(e)}")

# # Run the function
# run_ls_command()
