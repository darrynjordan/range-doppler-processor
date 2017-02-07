function [ Vco ] = getVco( frac_num )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

Vco = 25*(96 + frac_num/(2^24)) - 2400;

end

