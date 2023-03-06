run:
	g++ cpp_code/gradient_descend.cpp  -O0 -o cpp_code/gradient_descend
	cpp_code/./gradient_descend
	echo "cpp_code completed"
	
	g++ assembler_code/gradient_descend.cpp -O0 -o assembler_code/assembler_descend
	assembler_code/./assembler_descend
	echo "assembler code completed"
	
	g++ original_code/gradient_descend.s -no-pie -o original_code/original_descend
	original_code/./original_descend
	echo "original code completed"
