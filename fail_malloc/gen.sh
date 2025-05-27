gcc -shared -fPIC -o mock_malloc.so mock_malloc.c -ldl
LD_PRELOAD=./mock_malloc.so ../minishell