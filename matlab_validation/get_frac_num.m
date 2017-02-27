function [ fracNum ] = get_frac_num( Vco )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

fracNum = round((2^24)*((Vco*1e-6 + 2400)/25 - 96));

end

