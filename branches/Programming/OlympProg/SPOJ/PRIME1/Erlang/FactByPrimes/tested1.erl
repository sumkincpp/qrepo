-module(tested).
-export([main/0]).
%% ======================================================
-author('Fedor Sumkin - vompe@yandex.ru').
%% ======================================================

-import(lists, [flatten/1, reverse/1, 
		nth/2, map/2, keymember/3, foreach/2, 
		seq/2, sort/1, filter/2]).

-define (Debug, false).

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
            read_n_cases(In, Out, NCases)
    end.

%% ======================================================

read_n_cases(In, Out, NCases) ->
    if NCases > 0 ->
        case io:fread( In, " ","~d ~d" ) of
            eof -> true;
            {ok, [A, B]} ->
                foreach(fun(I) ->
                        case is_prime(I) of
                            true -> io:fwrite(Out, "~w~n", [I]);
                            false -> true
	                    end
                    end, seq(A,B)),
                io:fwrite(Out, "~n", []),
                read_n_cases(In, Out, NCases-1)
        end;
    true -> true
    end.
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
