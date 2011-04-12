package org.qosys.goeditor.editors;

import org.eclipse.core.runtime.CoreException;
import org.eclipse.jface.text.IDocument;
import org.eclipse.jface.text.IDocumentPartitioner;
import org.eclipse.jface.text.rules.FastPartitioner;
import org.eclipse.ui.editors.text.FileDocumentProvider;

public class GODocumentProvider extends FileDocumentProvider {

	protected IDocument createDocument(Object element) throws CoreException {
		IDocument document = super.createDocument(element);
//		int 
		if (document != null) {
			IDocumentPartitioner partitioner =
				new FastPartitioner(
					new GOPartitionScanner(),
					GOPartitionScanner.GoTokens
					/*new String[] {
						GOPartitionScanner.GO_SINGLELINE_COMMENT,
						GOPartitionScanner.GO_MULTILINE_COMMENT,
						GOPartitionScanner.GO_DECLARATION_WORD,
						GOPartitionScanner.GO_CONTROL_WORD
						
						}*/);
			partitioner.connect(document);
			document.setDocumentPartitioner(partitioner);
		}
		return document;
	}
}