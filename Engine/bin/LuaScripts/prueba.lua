
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

function pressKeyDoSomething(input,rig)
	if input:keyPressed(4) == true then
	print("Pulse A perros");
	 vec= Vector3(100,100,1000);
    rel= Vector3(0,0,0);
	rig:addForce1(vec,rel,1);
	end
end

function addTorque(rig)

    vec= Vector3(100,100,1000);
    rel= Vector3(0,0,0);
	rig:addTorque(vec,rel,1);
end


