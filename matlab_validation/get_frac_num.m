function [ fracNum ] = getFracNum( Vco )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

fracNum = (2^24)*((Vco*1e-6 + 2400)/25 - 96);

end

