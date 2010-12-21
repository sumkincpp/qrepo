-module(tested).
-export([main/0, pow_mod/3, mul_mod/3, fermat_prime/2, miller_rabin_prime/2]).
%% ======================================================
-author('Fedor Sumkin - vompe@yandex.ru').
%% ======================================================

-import(lists, [flatten/1, reverse/1, 
		nth/2, map/2, keymember/3, foreach/2, 
		seq/2, sort/1, filter/2]).

-define (Debug, false).
-define (MaxPrime, erlang:trunc(math:sqrt(1000000000))).
-define (MinHeapSize, 500).
-define (Iterations, 5).

main() ->
%%    {In, Out} = set_file_io(),
    {In, Out} = set_std_io(),
    loop(In, Out),
    checked_close2([In, Out]).

%% ======================================================

loop(In, Out) ->
    case io:fread( In, " ","~d" ) of
        eof ->
            true;
        {ok, [NCases]} ->
            pre_read_n_cases(In, Out, NCases)
    end.

%% ======================================================
pre_read_n_cases(In, Out, NCases) ->
    read_n_cases(In, Out, NCases).

read_n_cases(In, Out, NCases) ->
    if NCases > 0 ->
        case io:fread( In, " ","~d ~d" ) of
            eof -> true;
            {ok, [A, B]} ->
                if A == 1 orelse A == 2 -> io:fwrite(Out, "~w~n", [2]), A2 = 3;
                   true -> A2 = (A - A rem 2) + 1
                end,
                lists:foreach(fun(C) ->  
                    case miller_rabin_prime (C, ?Iterations) of
                        true ->    io:fwrite(Out, "~b~n", [C]);
                        false -> false
                    end
                end, lists:seq(A2, B, 2)),
                io:fwrite(Out, "~n", []),
                read_n_cases(In, Out, NCases-1)
        end;
    true -> true
    end.
%% ======================================================
%% Prime Check Library
%% ======================================================
%% Fermat Primarity
%% ======================================================
fermat_prime(1, Its) -> false;
fermat_prime(2, Its) -> true;
fermat_prime(P, Its) when P rem 2 == 0 -> false;
fermat_prime(P, Its) ->
    try lists:foreach(fun(I) -> 
            A = random:uniform(P-1), % 1...(P-1)
            Res = pow_mod(A, P-1, P),
            if Res /= 1 -> throw(not_prime);
                   true -> true        
            end
        end, lists:seq(1, Its)),
        true
    catch
        throw:not_prime -> 
            false
    end.

%% Miller Rabin Primarity
%% ======================================================

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
%% ======================================================
%% Math functions
%% ======================================================
pow(A, 1) -> A;
pow(A, N) ->
    A*pow(A, N-1).


pow2(A, N) ->
    pow2(A, N, A).
pow2(A, 1, Res) -> Res;
pow2(A, N, Res) ->
    pow2(A, N-1, Res*A).
%% ======================================================
%% FILE IO functions
%% ======================================================
checked_close2([First | Rest]) ->
    checked_close(First),
    if Rest == [] -> true;
       true -> checked_close2(Rest)    
    end. 

checked_close(IO) ->
    if IO == standard_io -> true;
       true -> file:close(IO)
    end.

set_std_io() ->
    {standard_io, standard_io}.

set_file_io() ->
    {ok, In} = file:open("in.txt", [read]),
    {ok, Out} = file:open("out.erl.txt", [write]),
    {In, Out}.

%% ========================================================
deb_out(Str) ->
    deb_out(Str, []).

deb_out(Str, Format) ->
    if ?Debug == true ->
        io:format(Str, Format);
    true -> true
    end.


