//
//  XMLParser.h
//  iPhoneLib,
//  Helper Functions and Classes for Ordinary Application Development on iPhone
//
//  Created by meinside on 09. 06. 30.
//
//  last update: 10.08.01.
//

#pragma once
#import <Foundation/Foundation.h>

#import "XMLParsedTree.h"
#import "XMLParsedElement.h"

#ifndef __IPHONE_4_0

@interface XMLParser : NSObject {
	
#else

//since __IPHONE_4_0
@interface XMLParser : NSObject <NSXMLParserDelegate> {
	
#endif

	NSXMLParser* parser;
	NSMutableString* currentElementValue;
	NSMutableArray* elementStack;
	
	XMLParsedElement* rootElement;
	XMLParsedTree* parsedTree;
	
	BOOL parsed;
	NSError* error;
	
	BOOL verbose;
}

- (id)initWithURL:(NSURL*)url;
- (id)initWithURLString:(NSString*)path;
- (id)initWithData:(NSData*)data;

- (void)pushElement:(XMLParsedElement*)element;
- (XMLParsedElement*)popElement;
- (XMLParsedElement*)peekElement;

- (void)setVerbose:(BOOL)verboseOrNot;

- (BOOL)parse;
- (BOOL)parsed;

+ (XMLParsedTree*)XMLParsedTreeFromURL:(NSURL*)url;
+ (XMLParsedTree*)XMLParsedTreeFromURLString:(NSString*)path;
+ (XMLParsedTree*)XMLParsedTreeFromData:(NSData*)data;

@property (retain, nonatomic) XMLParsedElement* rootElement;
@property (retain, nonatomic) XMLParsedTree* parsedTree;

@end


#ifndef __IPHONE_4_0

@interface XMLParser (XMLParserDelegate)

// Document handling methods
- (void)parserDidStartDocument:(NSXMLParser *)parser;
// sent when the parser begins parsing of the document.
- (void)parserDidEndDocument:(NSXMLParser *)parser;
// sent when the parser has completed parsing. If this is encountered, the parse was successful.

// DTD handling methods for various declarations.
- (void)parser:(NSXMLParser *)parser foundNotationDeclarationWithName:(NSString *)name publicID:(NSString *)publicID systemID:(NSString *)systemID;

- (void)parser:(NSXMLParser *)parser foundUnparsedEntityDeclarationWithName:(NSString *)name publicID:(NSString *)publicID systemID:(NSString *)systemID notationName:(NSString *)notationName;

- (void)parser:(NSXMLParser *)parser foundAttributeDeclarationWithName:(NSString *)attributeName forElement:(NSString *)elementName type:(NSString *)type defaultValue:(NSString *)defaultValue;

- (void)parser:(NSXMLParser *)parser foundElementDeclarationWithName:(NSString *)elementName model:(NSString *)model;

- (void)parser:(NSXMLParser *)parser foundInternalEntityDeclarationWithName:(NSString *)name value:(NSString *)value;

- (void)parser:(NSXMLParser *)parser foundExternalEntityDeclarationWithName:(NSString *)name publicID:(NSString *)publicID systemID:(NSString *)systemID;

- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName attributes:(NSDictionary *)attributeDict;
// sent when the parser finds an element start tag.
// In the case of the cvslog tag, the following is what the delegate receives:
//   elementName == cvslog, namespaceURI == http://xml.apple.com/cvslog, qualifiedName == cvslog
// In the case of the radar tag, the following is what's passed in:
//    elementName == radar, namespaceURI == http://xml.apple.com/radar, qualifiedName == radar:radar
// If namespace processing >isn't< on, the xmlns:radar="http://xml.apple.com/radar" is returned as an attribute pair, the elementName is 'radar:radar' and there is no qualifiedName.

- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName;
// sent when an end tag is encountered. The various parameters are supplied as above.

- (void)parser:(NSXMLParser *)parser didStartMappingPrefix:(NSString *)prefix toURI:(NSString *)namespaceURI;
// sent when the parser first sees a namespace attribute.
// In the case of the cvslog tag, before the didStartElement:, you'd get one of these with prefix == @"" and namespaceURI == @"http://xml.apple.com/cvslog" (i.e. the default namespace)
// In the case of the radar:radar tag, before the didStartElement: you'd get one of these with prefix == @"radar" and namespaceURI == @"http://xml.apple.com/radar"

- (void)parser:(NSXMLParser *)parser didEndMappingPrefix:(NSString *)prefix;
// sent when the namespace prefix in question goes out of scope.

- (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string;
// This returns the string of the characters encountered thus far. You may not necessarily get the longest character run. The parser reserves the right to hand these to the delegate as potentially many calls in a row to -parser:foundCharacters:

- (void)parser:(NSXMLParser *)parser foundIgnorableWhitespace:(NSString *)whitespaceString;
// The parser reports ignorable whitespace in the same way as characters it's found.

- (void)parser:(NSXMLParser *)parser foundProcessingInstructionWithTarget:(NSString *)target data:(NSString *)data;
// The parser reports a processing instruction to you using this method. In the case above, target == @"xml-stylesheet" and data == @"type='text/css' href='cvslog.css'"

- (void)parser:(NSXMLParser *)parser foundComment:(NSString *)comment;
// A comment (Text in a <!-- --> block) is reported to the delegate as a single string

- (void)parser:(NSXMLParser *)parser foundCDATA:(NSData *)CDATABlock;
// this reports a CDATA block to the delegate as an NSData.

- (NSData *)parser:(NSXMLParser *)parser resolveExternalEntityName:(NSString *)name systemID:(NSString *)systemID;
//// this gives the delegate an opportunity to resolve an external entity itself and reply with the resulting data.

- (void)parser:(NSXMLParser *)parser parseErrorOccurred:(NSError *)parseError;
// ...and this reports a fatal error to the delegate. The parser will stop parsing.

- (void)parser:(NSXMLParser *)parser validationErrorOccurred:(NSError *)validationError;
// If validation is on, this will report a fatal validation error to the delegate. The parser will stop parsing.
	
@end

#endif
