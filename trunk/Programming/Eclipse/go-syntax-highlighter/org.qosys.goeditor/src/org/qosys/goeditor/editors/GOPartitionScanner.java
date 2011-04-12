package org.qosys.goeditor.editors;

import java.util.ArrayList;
import java.util.List;

import org.eclipse.jface.text.rules.*;


public class GOPartitionScanner extends RuleBasedPartitionScanner {
	public final static String GO_MULTILINE_COMMENT = "__go_multiline_comment";
	public final static String GO_SINGLELINE_COMMENT = "__go_singleline_comment";
	public final static String GO_DECLARATION_WORD = "__go_declaration_word";
	public final static String GO_CONTROL_WORD = "__go_control_word";
	public final static String GO_STRING = "__go_string";
	public final static String GO_TASK = "__go_task";

	public static String[] GoTokens = {
		GO_MULTILINE_COMMENT, 
		GO_SINGLELINE_COMMENT, 
		GO_DECLARATION_WORD,
		GO_CONTROL_WORD,
		GO_STRING,
		GO_TASK
		};
	
	public static String[] declarationKeywords = {
		"struct", "func", "interface", "map", "chan", "package", "import", "type", 
		"const", "var" };	
	
	public static String[] controlWords = {
		"goto", "break", "continue", "if", "else", "switch", "default", "case", "for",
		"rabge", "go", "select", "return", "fallthrough", "defer"
		};

	public static String[] taskWords = {
		"TODO", "XXX", "FIXME" 
		};
	
	
	private class WordDetector implements IWordDetector {
		public boolean isWordPart(char character) {
			return isLetter(character) || Character.isDigit(character);
			}
		
		public boolean isWordStart(char character) {
			return isLetter(character);
			}
		
		private boolean isLetter(char character) {
			return Character.isLetter(character) || character == '_';
			}
		}

	
	public GOPartitionScanner() {

        PredicateWordRule keywordRule = new PredicateWordRule(new WordDetector(), 
        		declarationKeywords, 
        		new Token(GO_DECLARATION_WORD));
        
        keywordRule.addWords(controlWords, new Token(GO_CONTROL_WORD));

		List<IPredicateRule> rules = new ArrayList<IPredicateRule>();
		
        rules.add(keywordRule);
//        rules.add(new PredicateWordRule(new WordDetector(),controlWords, new Token(GO_CONTROL_WORD)));
		rules.add(new MultiLineRule("/*", "*/", new Token(GO_MULTILINE_COMMENT)));
		rules.add(new SingleLineRule("//", "", new Token(GO_SINGLELINE_COMMENT)));
		rules.add(new SingleLineRule("\"", "\"", new Token(GO_STRING), '\\'));
		rules.add(new SingleLineRule("'", "'", new Token(GO_STRING), '\\'));
		
		IPredicateRule[] result = new IPredicateRule[rules.size()];
		rules.toArray(result);
		setPredicateRules(result);
	}
}
