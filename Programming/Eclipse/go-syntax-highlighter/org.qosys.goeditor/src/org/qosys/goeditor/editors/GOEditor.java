package org.qosys.goeditor.editors;

import org.eclipse.ui.editors.text.TextEditor;

public class GOEditor extends TextEditor {

	private ColorManager colorManager;

	public GOEditor() {
		super();
		colorManager = new ColorManager();
		setSourceViewerConfiguration(new GOConfiguration(colorManager));
		setDocumentProvider(new GODocumentProvider());
	}
	public void dispose() {
		colorManager.dispose();
		super.dispose();
	}

}
