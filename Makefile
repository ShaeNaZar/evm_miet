run:
	g++ original_code/gradient_descend.cpp  -O0 -o original_code/gradient_descend
	original_code/./gradient_descend
	echo "original_code completed"
	
	g++ inserted_code/gradient_descend.cpp -O0 -o inserted_code/gradient_descend
	inserted_code/./gradient_descend
	echo "inserted_code completed"
	
