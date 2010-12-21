-module(fread).
-author('').

-export([main/0]).
-export([get_processed_list/1]).


main() ->
    {ok, InFile} = file:open("test.txt", [read]),
    Data = readl_file(InFile),
    write_to_file("test.out.txt", Data),
    ok = file:close(InFile),
    Data.
%% ==============================================
get_processed_list([First | Rest]) ->
    N = get_processed_list(Rest, [First]),
    lists:reverse(N).

get_processed_list([], Data) ->
    Data;
get_processed_list([First | Rest], Data) when First == 42 ->
    Data;
get_processed_list([First | Rest], Data) ->
   get_processed_list(Rest, [First | Data]).

%% ==============================================
write_to_file(File, Data) ->
    {ok, OutFile} = file:open(File, [write]),
    io:fwrite(OutFile, Data, []),
    ok = file:close(OutFile),
    Data.
%% ==============================================
%% Read File By strings in it(spaces ignored)
%% ==============================================
read_file(File) ->
    read_file(File, []).

read_file(File, Data) ->
    case io:fread(File, "", "~s") of
        {ok, [N]} -> 
            read_file(File, [N | Data]);
        eof ->
            lists:reverse(Data)
    end.
%% ==============================================
%% Read File by lines and get all contents
%% ==============================================
readl_file(IoDevice) ->
   readl_file(IoDevice, []).

readl_file(IoDevice, InData) ->
   case file:read_line(IoDevice) of
     {'ok', Data}  ->
       readl_file(IoDevice, [Data | InData]);
     eof ->
       lists:reverse(InData)
    end. 


