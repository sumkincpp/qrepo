package org.qosys.goeditor.editors;

//import org.eclipse.jface.text.IDocument;
//import org.eclipse.jface.text.ITextDoubleClickStrategy;
import org.eclipse.jface.text.TextAttribute;
import org.eclipse.jface.text.presentation.IPresentationReconciler;
import org.eclipse.jface.text.presentation.PresentationReconciler;
//import org.eclipse.jface.text.rules.DefaultDamagerRepairer;
//import org.eclipse.jface.text.rules.Token;
import org.eclipse.jface.text.source.ISourceViewer;
import org.eclipse.jface.text.source.SourceViewerConfiguration;
import org.eclipse.swt.graphics.RGB;
import org.eclipse.swt.SWT;


public class GOConfiguration extends SourceViewerConfiguration {
	private ColorManager _colorManager;

	public GOConfiguration(ColorManager colorManager) {
		this._colorManager = colorManager;
	}
	public String[] getConfiguredContentTypes(ISourceViewer sourceViewer) {
		return GOPartitionScanner.GoTokens;
				/*new String[] {
			GOPartitionScanner.GO_MULTILINE_COMMENT,
			GOPartitionScanner.GO_SINGLELINE_COMMENT,
			GOPartitionScanner.GO_DECLARATION_WORD,
			GOPartitionScanner.GO_CONTROL_WORD
			};*/
	}

	/**
	 * Repair - Damager
	 * */
	public void addRD(PresentationReconciler r, String contentType, RGB color) {
		
		NonRuleBasedDamagerRepairer ndr =
				new NonRuleBasedDamagerRepairer(
						new TextAttribute(_colorManager.getColor(color)));
		
		r.setDamager(ndr, contentType);
		r.setRepairer(ndr, contentType);	
		}
	
	public IPresentationReconciler getPresentationReconciler(ISourceViewer sourceViewer) {
		PresentationReconciler reconciler = new PresentationReconciler();
		
		registerScannerBoldForContentType(reconciler, 
				GOPartitionScanner.GO_DECLARATION_WORD, IGOColorConstants.KEYWORD);

		registerScannerBoldForContentType(reconciler, 
				GOPartitionScanner.GO_CONTROL_WORD, IGOColorConstants.CONTROL_WORD);

		addRD(reconciler, 
				GOPartitionScanner.GO_STRING, IGOColorConstants.STRING);

		addRD(reconciler, 
				GOPartitionScanner.GO_MULTILINE_COMMENT, IGOColorConstants.COMMENT);

		addRD(reconciler, 
				GOPartitionScanner.GO_SINGLELINE_COMMENT, IGOColorConstants.COMMENT);
		
		
/*		NonRuleBasedDamagerRepairer ndr =
			new NonRuleBasedDamagerRepairer(
				new TextAttribute(
					colorManager.getColor(IGOColorConstants.GO_COMMENT)));
		
		reconciler.setDamager(ndr, GOPartitionScanner.GO_MULTILINE_COMMENT);
		reconciler.setRepairer(ndr, GOPartitionScanner.GO_MULTILINE_COMMENT);*/

		return reconciler;
		}
	
    private void registerScannerBoldForContentType(
            PresentationReconciler reconciler, String contentType, RGB color) {
    	
        final TextAttribute textAttribute = new TextAttribute(this._colorManager
                .getColor(color), null, SWT.BOLD);
        
        final NonRuleBasedDamagerRepairer damagerRepairer = new NonRuleBasedDamagerRepairer(
                textAttribute);
        reconciler.setDamager(damagerRepairer, contentType);
        reconciler.setRepairer(damagerRepairer, contentType);
    	}
	}