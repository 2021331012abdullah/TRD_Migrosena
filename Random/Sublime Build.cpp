{
  "shell_cmd": "g++ -std=c++20 \"${file}\" -o \"${file_path}/${file_base_name}\" && timeout 5s \"${file_path}/${file_base_name}\"< input.txt > output.txt  && rm \"${file_path}/${file_base_name}\"",
  "file_regex": "^(..[^:]*):([0-9]+):?([0-9]+)?:? (.*)$",
  "working_dir": "${file_path}",
  "selector": "source.c++",
  "variants":
  [
    {
      "name": "debug + input output",
      "shell_cmd": "g++ -DLOCAL -std=c++17  -Wshadow -Wall \"$file_name\" -o \"$file_base_name\"  -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -g && timeout 5s \"${file_path}/${file_base_name}\"< input.txt > output.txt  && rm \"${file_path}/${file_base_name}\""
    },
  ]
}