-module(tested).
-export([main/0]).

main() ->
%%    {In, Out} = set_file_io(),
    {In, Out} = set_std_io(),
    loop(In, Out),
    checked_close2([In, Out]).

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
    
loop(In, Out) ->
    case io:fread( In, " ","~d" ) of
        eof ->
            true;
        {ok, [X]} ->
            if
                X == 42 -> true;
                true ->
                    io:fwrite(Out, "~B\n", [X] ),
                    loop(In, Out)
            end
    end.
