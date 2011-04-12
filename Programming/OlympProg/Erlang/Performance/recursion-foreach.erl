-module('recfor').
%% ======================================================
-author('Fedor Sumkin - vompe@yandex.ru').
%% ======================================================
-export([main/0]).

-define(Iterations, 10000).

main () ->
%    PID = spawn(recfor, out_process, [0]), 
    io:format("Taking ~b Iterations", [?Iterations]).
%    test_foreach(),
%    PID ! {timestamp, "test_foreach/0 completed"},
%    test_recursion(),
%    PID ! {timestamp, "test_rescursion/1 completed"},
%    PID ! finish.

out_process(TimeSec) ->
    receive
        {timestamp, Mess} ->
            io:format("~w - ~b seconds~n",[Mess, TimeSec]),
            out_process(TimeSec);
        finish -> true
    end.

test_foreach() ->
    lists:foreach(fun(I) ->
        test_action(I)
    end, lists:seq(1, ?Iterations)).

test_recursion() ->
    test_recursion(1).

test_recursion(N) when N > ?Iterations -> true;
test_recursion(N) ->
    test_action(N), 
    test_recursion(N+1).

test_action(A) ->
    A*A.
