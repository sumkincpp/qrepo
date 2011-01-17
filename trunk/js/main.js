$(document).ready(function()    {
	$("#process_button").click(function () { 
		var text = $("#in").html();
		
		text = parse_wiki (text);
		
		$("#out").html(text);
		
		});
    });

function parse_wiki (text) {
	text = text.replace(/\*\*(.*?)\*\*/i, "\\textbf{$1}");
	text = text.replace(/\[\[(.*?)\|(.*?)\]\]/i, "\\href{$1}{$2}");
	text = text.replace(/\[\[([^\n|]*?)\]\]/i, "\\url{$1}");
	text = parse_enums(text);
	
	return text;
	}

function parse_enums (text) {
	text = parse_enum (text, "-", "enumerate");
	text = parse_enum (text, "*", "itemize");
	
	return text;
	}
	
function parse_enum(text, del, style) {
	// Simple enumerate Parse
	// /^   \* (.*)/mgi
	var re = "";
	if (del == "-")
		re = /^   \- (.*)/mgi;
	else 
		re = /^   \* (.*)/mgi;
		
	text = text.replace(re, function($0, $1, $2, $3, $4, $5) {
		var isStart = false;
		var isEnd = false;
		
		//isItEndOfEnumeration ?
		if (compare($3, $2 + $0.length + 1, "   "+del+" ") == false) {
			isEnd = true;
			}
		//isItStartOfEnumeration ?
		
		for (var i = 2; ; i++) {
			if ($2 - i <= 0) break;
			if ($3[$2 - i] == '\n') {
				if (compare($3, $2 - i + 1, "   "+del+" ") == false) {
					isStart = true;
					break;
					}
				break;
				}
			}
					
		return (isStart ? "\\begin{"+style+"}\n" : "") + 
				"   \\item " + $1 + "" + 
			   (isEnd ? "\n\\end{"+style+"}" : "");
	});
	return text;
	}
	
function compare(str1, off, str2) {
	for (var i = 0; i < str2.length; i++)
		{
		if (str1[off + i] != str2[i]) {
			return false;
			}
		}
	return true;
	}


	
//process_button