<?php
/*
http://deplate.sourceforge.net/Markup.html#hd0010005

*/

function parse_wiki ($text) {
	$text = preg_replace("/\*\*(.*?)\*\*/i", "\\textbf{ $1}", $text); // Bold Style **bold**
	$text = preg_replace("/\[\[(.*?)\|(.*?)\]\]/i", "\\href{ $1}{ $2}", $text); //Href [[http://ya.ru|Yandex]]
	$text = preg_replace("/\[\[([^\n|]*?)\]\]/i", "\\url{ $1}", $text); //url [[http://ya.ru]]

    $text = preg_replace("/[=-]{7,}/mi", "\\hline", $text);
    $text = preg_replace("/======(.*?)======/mi", "\\chapter{ $1}", $text);
    $text = preg_replace("/=====(.*?)=====/mi", "\\section{ $1}", $text);
    $text = preg_replace("/====(.*?)====/mi", "\\subsection{ $1}", $text);
    $text = preg_replace("/===(.*?)===/mi", "\\subsubsection{ $1}", $text);

    $text = preg_replace("/\<code cpp\>(.*?)\<\/code\>/si", "\\begin{quote}\n\\begin{verbatim}\n $1 \n\\end{verbatim}\n\\end{quote}", $text);

//    $text = preg_replace("/(={6})(.*?)\1/mi", "\\chapter{ $2}", $text);
//    $text = preg_replace("/(={5})(.*?)\1/mi", "\\section{ $2}", $text);

//	$text = parse_enums($text); // Non nested enumerates
    $text = parse_enums2($text);	

	return $text;
	}


function parse_enums2 ($text) {
	$text = parse_enum2 ($text,   "   - ", "enumerate");
	$text = parse_enum2 ($text, "     - ", "enumerate");
	$text = parse_enum2 ($text,   "   * ", "itemize");
	$text = parse_enum2 ($text, "     * ", "itemize");
	
	return $text;
	}
/*

TODO : hold nested tags, for example :
   * <code>fsdfsd
fsdfsdfsd
fsd
fsd
fsd</code>
  * 
*/
function parse_enum2 ($text, $del, $style) {
    
    $par = "\n".$del; //named by paragraph

    $pos = strpos($text, $par);
    
    if ($pos === false) { return $text; }
    else {
        $start_pos = $pos + strlen($par);

        $start = substr($text, 0, $pos);
        $start .= "\n\begin{".$style."}"."\n";
        $end =  substr($text, $start_pos);

        $endl_pos = 0;
        while (1) 
            {
/*
            echo "+++++++++++++++++++++++++\n";
            echo " [[".substr($end, 0, $endl_pos)."]] ";
*/
            $endl_pos = strpos($end, "\n", $endl_pos);
/*
            echo " [[".substr($end, 0, $endl_pos)."]] ";
            echo "=========================\n";
*/
            if (substr_compare($end, $par, $endl_pos, strlen($par)) === 0) {
                //echo "First level\n";
                $start .= "\item ".substr($end, 0, $endl_pos). "\n";
                $end = substr($end, $endl_pos + strlen($par));
                $endl_pos = 0;
                }
            elseif (substr_compare($end, "\n  ".$del, $endl_pos, strlen($del) + 3) === 0) {
                $endl_pos += strlen($del) + 3;
                //echo "Second level\n";
                }
            else { 
                $start .= "\item ".substr($end, 0, $endl_pos). "\n";
                $start .= "\end{".$style."}";
                $start .= substr ($end, $endl_pos);
                break ;
                }
            }

        return parse_enum2 ($start, $del, $style);
        }
    
    return $text;
    }

$fname = "code-formatting.txt";
	
$text = file_get_contents($fname); //"algo2.txt"
	
$new = parse_wiki ($text);

$fp = fopen($fname.".tex", 'w');
fwrite($fp, $new);
fclose($fp);
?>
