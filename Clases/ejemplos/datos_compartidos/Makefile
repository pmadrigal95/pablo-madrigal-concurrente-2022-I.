compile:
	cc -g example.c -Wall -Wextra -o example -pthread

msan:
	clang -g example.c -fsanitize=memory -Wall -Wextra -o example_msan -pthread

asan:
	clang -g example.c-fsanitize=address -Wall -Wextra -o example_asan -pthread

tsan:
	clang -g example.c -fsanitize=thread -Wall -Wextra -o example_tsan -pthread