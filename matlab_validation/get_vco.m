function [ vco ] = get_vco( frac_num )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

vco = (25*(96 + frac_num/(2^24)) - 2400)*1e6;

end

