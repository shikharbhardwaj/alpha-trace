function rotation_matrix_demo

	disp("Picking random Euler angles (radians)");

	x = 2*pi*rand() - pi % -180 to 180
	y = pi*rand() - pi*0.5 % -90 to 90
	z = 2*pi*rand() - pi % -180 to 180

	disp("\nRotation matrix is:");
  sample = eye(3,3);
  
	  sample(1, 1) = 0.871214;
    sample(1, 2) = 0;
    sample(1, 3) = -0.490904;
    sample(2, 1) = -0.192902;
    sample(2, 2) = 0.919559;
    sample(2, 3) = -0.342346;
    sample(3, 1) = 0.451415;
    sample(3, 2) = 0.392953;
    sample(3, 3) = 0.801132;
    
	R = compose_rotation(x,y,z)
	
	disp("Decomposing R");
	[x2,y2,z2] = decompose_rotation(sample)

	disp("");
	err = sqrt((x2-x)*(x2-x) + (y2-y)*(y2-y) + (z2-z)*(z2-z))

	if err < 1e-5
		disp("Results are correct!");
	else
		disp("Oops wrong results :(");
	end
end

function [x,y,z] = decompose_rotation(R)
	x = atan2(R(3,2), R(3,3));
	y = atan2(-R(3,1), sqrt(R(3,2)*R(3,2) + R(3,3)*R(3,3)));
	z = atan2(R(2,1), R(1,1));
end

function R = compose_rotation(x, y, z)
	X = eye(3,3);
	Y = eye(3,3);
	Z = eye(3,3);

    X(2,2) = cos(x);
    X(2,3) = -sin(x);
    X(3,2) = sin(x);
    X(3,3) = cos(x);

    Y(1,1) = cos(y);
    Y(1,3) = sin(y);
    Y(3,1) = -sin(y);
    Y(3,3) = cos(y);

    Z(1,1) = cos(z);
    Z(1,2) = -sin(z);
    Z(2,1) = sin(z);
    Z(2,2) = cos(z);

	R = Z*Y*X;
end
