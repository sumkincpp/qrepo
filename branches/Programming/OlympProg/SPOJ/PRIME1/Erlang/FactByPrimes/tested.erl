-module(tested).
-export([main/0, eratos_primes/1, case_process/5, receive_process/3]).
%% ======================================================
-author('Fedor Sumkin - vompe@yandex.ru').
%% ======================================================

-import(lists, [flatten/1, reverse/1, 
		nth/2, map/2, keymember/3, foreach/2, 
		seq/2, sort/1, filter/2]).

-define (Debug, false).
-define (MaxPrime, erlang:trunc(math:sqrt(1000000000))).
-define (MinHeapSize, 500).

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

sleep(Time) ->
    receive
        after Time ->
            true
    end.

%% ======================================================
pre_read_n_cases(In, Out, NCases) ->
    Primes = eratos_primes(?MaxPrime),
    io:format("Processes : ~b ~n", [NCases]),
    PPID = spawn(tested, receive_process, [Out, NCases, self()]),
    CPID = read_n_cases(In, Out, NCases, Primes, PPID),
    receive
        finish_main -> true
    end.
%    spawn(tested, stop_process, [PPID, NCases]). 

%Primes
%    read_n_cases(In, Out, NCases, Primes, PPID).
%    receive_process(NCases).

%% PPID - Parent PID
read_n_cases(In, Out, N, Primes, PPID) ->
     if N == 0 orelse N < 0 -> true; 
        N > 0 ->
        case io:fread( In, " ","~d ~d" ) of
            eof -> true;
            {ok, [A, B]} ->
                spawn_opt(tested, case_process, [A, B, N, PPID, Primes], [{priority, high}, {min_heap_size,?MinHeapSize} ]), %Primes
                read_n_cases(In, Out, N-1, Primes, PPID)
        end;
    true -> true
    end.

receive_process(Out, N, MPID) ->
     if N == 0 orelse N < 0 -> true; 
        N > 0 ->
            receive
                {N, finished} -> 
                    io:fwrite(Out, "~n", []),
                    io:format("Processed ~w~n", [N]),
                    receive_process(Out, N-1, MPID);
                {N, C} -> 
                    io:fwrite(Out, "~w~n", [C]),
                    receive_process(Out, N, MPID)
            end;
        true -> true
    end,
    MPID ! finish_main.
    
case_process(A, B, N, PPID, Primes) ->
    io:format("Case_Process #~b! A = ~b, B = ~b ~n", [N, A, B]),
    if A == 1 orelse A == 2 -> 
           PPID ! {N, 2},
           A2 = 3;
       true -> A2 = (A - (A rem 2)) + 1
    end,
    lists:foreach(fun(C) ->  
        try lists:foreach(
            fun(I) ->
                if %%TODO: think about checkeness
                   C rem I == 0 andalso C /= I -> throw(stop);
                   true -> true
                end
            end, Primes),
                PPID ! {N, C},
                %io:format("Sending! ~b ~n", [C]),
            true
        catch
            throw:stop -> 
                false
        end
    end, lists:seq(A2, B, 2)),
    PPID ! {N, finished},
    true.
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
