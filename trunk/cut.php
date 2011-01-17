/**
 * function for parsing enumerates
 *
*/

function parse_enums ($text) {
	$text = parse_enum ($text, "-", "enumerate");
	$text = parse_enum ($text, "*", "itemize");
	
	return $text;
	}
	
function parse_enum($text, $del, $style) {
	$re = "/(^   \\".$del." ([^\n]*?))$/mi";
		
	preg_match_all($re, $text, $matches, PREG_OFFSET_CAPTURE);
	
	$enum_str = "   $del ";
	$enum_str_len = strlen($enum_str);
	
	$prev = 0;
	$next = 0;
	$res = "";
    
    //XXX: if no matches => sizeof($matches[1]) == 0
	
	for ($j = 0; $j < sizeof($matches[1]); $j++) {
		$match = $matches[1][$j];
		$off = $match[1]; //offset
//        echo "[[".$match[0]. "]]\n" . $off. "\n";
		
		$isStart = 0;
        //Searching previous line for enum delimetr
		for ($i = 2;; $i++) {
			if ($text[$off - $i] == "\n") {
				$res .= substr($text, $prev, $off-$prev);
				$prev = $off + strlen($matches[0][$j][0])+1;

                // first enum_str_le symbols on previous line. If it is
                // enum delimeter - it is continue
				$line_start = substr($text, $off - $i + 1, $enum_str_len); 
				
				if (strcmp($line_start, $enum_str) == 0) $isStart = 0;
				else $isStart = 1;

/*                echo "Previous line starting with {".$line_start. "}\n";
				echo "iStart : ".$isStart; 
*/				
				break;
				}
			}
        //Going Forward to search next enum delimeter
        $isEnd = 1;

        $off = $off + strlen($matches[1][$j][0]);
        $line_start = substr($text, $off + 1, $enum_str_len); 

        if (strcmp($line_start, $enum_str) == 0) {
            $isEnd = 0;
            }
        else {
            // TODO: search for starting - nested lists
            }

        if ($isStart) $res .= "\begin{".$style."}\n";
        $res .= "   \item ".$matches[2][$j][0]."\n";
        if ($isEnd) $res .= "\end{".$style."}\n";
		}
    $res .= substr($text, $prev, strlen($text)-$prev);
//	echo $res;

	return $res;
	}