function testA(a)
	print("call c++ part");
	globalFunction();
	a:action();
	a:doPrint(1,2);
end

function testAAndB(a, b)
	print("A and B");
	globalFunction();
	a:action();
  	a:doPrint(1,2);
	
	b:hello("Good using c++ and Lua");
end



