-module(tested).
-export([main/0, eratos_primes/1]).
%% ======================================================
-author('Fedor Sumkin - vompe@yandex.ru').
%% ======================================================

-import(lists, [flatten/1, reverse/1, 
		nth/2, map/2, keymember/3, foreach/2, 
		seq/2, sort/1, filter/2]).

-define (Debug, false).
-define (MaxPrime, erlang:trunc(math:sqrt(1000000000))).

main() ->
    {In, Out} = set_file_io(),
%%    {In, Out} = set_std_io(),
    loop(In, Out),
    checked_close2([In, Out]).

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
    Primes = eratos_primes(?MaxPrime),
    read_n_cases(In, Out, NCases, Primes).

read_n_cases(In, Out, NCases, Primes) ->
    if NCases > 0 ->
        case io:fread( In, " ","~d ~d" ) of
            eof -> true;
            {ok, [A, B]} ->
                if A == 1 orelse A == 2 -> io:fwrite(Out, "~w~n", [2]), A2 = 3;
                   true -> A2 = (A - A rem 2) + 1
                end,
                lists:foreach(fun(C) ->  
                    case is_fermat_prime(C) of
                       true -> io:fwrite(Out, "~w~n", [C]);
                       false -> true
                    end
                end, lists:seq(A2, B, 2)),
                io:fwrite(Out, "~n", []),
                read_n_cases(In, Out, NCases-1, Primes)
        end;
    true -> true
    end.
%% ======================================================
pow(A, 1, M) ->
     A rem M;
pow(A, 2, M) ->
     A*A rem M;
pow(A, B, M) ->
     B1 = B div 2,
     B2 = B - B1,
     %% B2 = B1 or B1+1
     P = pow(A, B1, M),
     case B2 of
         B1 -> (P*P) rem M;
         _  -> (P*P*A) rem M
     end.

make(N) -> new_seed(), make(N, 0).

make(0, D) -> D;
make(N, D) ->
    make(N-1, D*10 + (random:uniform(10)-1)).

new_seed() ->
     {_,_,X} = erlang:now(),
     {H,M,S} = time(),
     H1 = H * X rem 32767,
     M1 = M * X rem 32767,
     S1 = S * X rem 32767,
     put(random_seed, {H1,M1,S1}).

is_fermat_prime(D) ->
%    new_seed(),
    is_fermat_prime(D, 100).

is_fermat_prime(D, Ntests) ->
    N = length(integer_to_list(D)) -1,
    if  D == 2 orelse D == 3 orelse D == 5 orelse D == 7 -> true;
        N == 0 -> false;
        true -> is_fermat_prime(Ntests, D, N)
    end.

is_fermat_prime(0, _, _) -> true;
is_fermat_prime(Ntest, N, Len) ->
    K = random:uniform(Len),
    %% A is a random number less than N 
    A = make(K),
    if 
     A < N ->
         case pow(A,N,N) of
             A -> is_fermat_prime(Ntest-1,N,Len);
             _ -> false
         end;
     true ->
         is_fermat_prime(Ntest, N, Len)
    end.
%% ======================================================

eratos_primes(Prime, Max, Primes,Integers) when Prime > Max ->
    lists:reverse(Primes) ++ Integers;
eratos_primes(Prime, Max, Primes, Integers) ->
    [NewPrime|NewIntegers] = [ X || X <- Integers, X rem Prime =/= 0 ],
    eratos_primes(NewPrime, Max, [Prime|Primes], NewIntegers).

eratos_primes(N) ->
    eratos_primes(2, round(math:sqrt(N)), [], lists:seq(3,N,2)).

%% ======================================================

generate_primes(Max) ->
    sundaram_nprimes(Max).

sundaram_nprimes(Max) ->
    foreach(fun(I) ->
        foreach(fun(J) ->
            true
%            N = I + J + 2 * I * J,
%            if N  < Max -> Primes ++ N;
%                true -> true
%            end
        end, seq(1,I))
    end, seq(1,(Max-1)/3)).
%% ======================================================
%% Function Library \/
%% ======================================================
ceiling(X) ->
    T = erlang:trunc(X),
    case (X - T) of
        Neg when Neg < 0 -> T;
        Pos when Pos > 0 -> T + 1;
        _ -> T
    end.

%% ======================================================
is_prime(A) ->
    if
        A < 0 -> {error, "negative"};
        A == 1 -> false;
        A == 2 -> true;
        true ->
            is_prime(A, 3, ceiling(math:sqrt(A)))
    end.
%% ======================================================
is_prime(A, Curr, En) -> 
    if 
       Curr > En -> 
            true;
       (A rem Curr) == 0 -> 
            false;
       true -> is_prime(A, Curr + 2, En)
    end.

%% ======================================================

deb_out(Str, Format) ->
    if ?Debug == true ->
        io:format(Str, Format);
    true -> true
    end.

%generate_primes(st, en, Gen) ->
%    true.
    
%% ======================================================
%            if
%                X == 42 -> true;
%                true ->
%                    io:fwrite(Out, "~B\n", [X] ),
%                    loop(In, Out)
%            end

%% ======================================================

% curr - atom!
