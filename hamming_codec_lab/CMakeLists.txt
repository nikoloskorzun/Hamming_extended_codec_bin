include_directories("hamming_codec", "app")	
add_subdirectory("hamming_codec")	

add_executable(main "main.cpp" "App.cpp" "App.h")	# Создает исполняемый файл с именем main



target_link_libraries(main hamming_codec)