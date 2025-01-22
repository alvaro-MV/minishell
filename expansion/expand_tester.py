import subprocess

compilation_str = "cc -g ../expansion/expand.c ../data_structs/dictionary.c ../data_structs/dictionary2.c ../tokenizer/tokenizer_utils.c ../data_structs/dynamic_array.c ../libft/libft.a"
compilation = subprocess.run(compilation_str.split(' '))

result = subprocess.run(['./a.out', '$BAR\'ooo\''], capture_output=True, text=True)
print(result.stdout)
expected = subprocess.run(['echo', "ooo"], capture_output=True, text=True)
print(expected.stdout)

if (result.stdout != expected.stdout):
	print('[KO]')
else:
	print('[OK]')

