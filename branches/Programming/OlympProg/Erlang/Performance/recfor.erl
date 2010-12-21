-module('recfor').
%% ======================================================
-author('Fedor Sumkin - vompe@yandex.ru').
%% ======================================================
-export([main/0, out_process/0]).

-define(Iterations, 1000000).
-define (MRIterations, 50).

main () ->
    PID = spawn(recfor, out_process, []), 
    io:format("Taking ~b Iterations ~n", [?Iterations]),
    test_foreach(),
    PID ! {timestamp, "test_foreach/0 completed"},
    test_recursion(),
    PID ! {timestamp, "test_recursion/1 completed"},
    PID ! finish.

out_process() ->
    TS1 = calendar:datetime_to_gregorian_seconds(calendar:universal_time()),
    receive
        {timestamp, Mess} ->
            TS2 = calendar:datetime_to_gregorian_seconds(calendar:universal_time()),
            Dt = TS2 - TS1,
            io:format("~p, ~b seconds~n",[Mess, Dt]),
            out_process();
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
    miller_rabin_prime(A, ?MRIterations).




miller_rabin_prime(1, Its) -> false;
miller_rabin_prime(2, Its) -> true;
miller_rabin_prime(P, Its) when P rem 2 == 0 -> false;
miller_rabin_prime(P, Its) ->
    S = miller_rabin_divide_S(P - 1),
    try lists:foreach(fun(I) -> 
            A = random:uniform(P-1), % 1...(P-1)
            {Temp, Mod} = miller_rabin_count_temp_mod(S, pow_mod(A, S, P), P),
            if Mod /= P-1 andalso (Temp rem 2) == 0 -> throw(not_prime);
                   true -> true        
            end
        end, lists:seq(1, Its)),
        true
    catch
        throw:not_prime -> 
            false
    end.

miller_rabin_count_temp_mod(Temp, Mod, P) 
    when Temp == P-1 orelse 
          Mod ==   1 orelse 
          Mod == P-1 -> {Temp, Mod};
miller_rabin_count_temp_mod(Temp, Mod, P) ->
    miller_rabin_count_temp_mod(Temp*2, mul_mod(Mod, Mod, P), P).

miller_rabin_divide_S(P) when P rem 2 /= 0 -> P;
miller_rabin_divide_S(P) -> miller_rabin_divide_S(trunc(P/2)).


%% ======================================================
%% A^B mod C, uses Exponentiation  by squarization - fast pow algo
%% ======================================================
%% (7^107)%9 = 4
%% ======================================================
pow_mod(A, B, C) ->
%    deb_out("A B C X Y~n"),
    pow_mod(A, B, C, 1, A).

pow_mod(A, 0, C, X, Y) -> X rem C;
pow_mod(A, B, C, X, Y) ->
%    deb_out("~b ~b ~b ~b ~b ~n", [A, B, C, X, Y]),
    if B rem 2 == 1 ->
        X2 = (X*Y) rem C;
        true -> X2 = X, true
    end,
    pow_mod (A, trunc(B/2), C, X2,(Y*Y) rem C).

%% ======================================================
%% A*B % C =>
mul_mod(A, B, C) ->
    mul_mod(A, B, C, 0, A rem C).

mul_mod(A, 0, C, X, Y) -> X rem C;
mul_mod(A, B, C, X, Y) ->
%    deb_out("~b ~b ~b ~b ~b ~n", [A, B, C, X, Y]),
    if B rem 2 == 1 ->
        X2 = (X+Y) rem C;
        true -> X2 = X, true
    end,
    mul_mod (A, trunc(B/2), C, X2,(Y*2) rem C).
