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

function setPosition(rig)

    vec= Vector3(200,0,0);
	rig:setPosition(vec);
end


function addForce(rig)

    vec= Vector3(100,100,1000);
    rel= Vector3(0,0,0);
	rig:addForce1(vec,rel,1);
end

function setgravity(rig)

    vec= Vector3(0,10,0);
	rig:setGravity(vec);
end




