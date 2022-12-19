size = 40;
arctanDec = int16(zeros(1,size));
arctan = zeros(1,size);
poweroftwo = int16(zeros(1,size));
p=1;
q15 = 2^15;
q12 = 2^12;
for j=0:size-1
    arctanDec(p) = int16(atan(2^-j)*q12);
    arctan(p) = atan(2^-j);
    poweroftwo(p) = int16((2^-j)*q12);
    p=p+1;
end

%%
%ângulo para calculo seno e cos
sincos = zeros(10,3);
sincos(1:10) = -2*pi + (2*pi+2*pi).*rand(10,1);
sincos(1:10,2) = sin(sincos(1:10));
sincos(1:10,3) = cos(sincos(1:10));
%%
%div e mult
divmul = zeros(10,4);
divmul(1:10) = -8 + (7.99+8).*rand(10,1);
divmul(1:10,2) = -8 + (7.99+8).*rand(10,1);
divmul(1:10,3) = divmul(1:10).*divmul(1:10,2);
divmul(1:10,4) = divmul(1:10)./divmul(1:10,2);


