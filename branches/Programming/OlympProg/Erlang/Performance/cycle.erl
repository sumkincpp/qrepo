-module('cycle').

-export([main/0]).

-define(Iterations, 10000).

main () ->
    lists:foreach(fun(C) ->
        io:format
    end, lists:seq(1, 1000)),
    true.
