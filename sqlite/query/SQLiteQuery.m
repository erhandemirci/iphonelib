/*
 Copyright (c) 2010, Sungjin Han <meinside@gmail.com>
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  * Neither the name of meinside nor the names of its contributors may be
    used to endorse or promote products derived from this software without
    specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
 */
//
//  SQLiteQuery.m
//  iPhoneLib,
//  Helper Functions and Classes for Ordinary Application Development on iPhone
//
//  Created by meinside on 09. 12. 20.
//
//  last update: 10.06.28.
//

#import "SQLiteQuery.h"


@implementation SQLiteQuery

#pragma mark -
#pragma mark initializer

- (id)initWithQueryString:(NSString*)aQuery
{
	if(self = [super init])
	{
		query = [aQuery copy];
		values = [[NSMutableArray alloc] init];
	}
	
	return self;
}

+ (SQLiteQuery*)queryWithQueryString:(NSString*)aQuery
{
	return [[[SQLiteQuery alloc] initWithQueryString:aQuery] autorelease];
}

#pragma mark -
#pragma mark add params

- (id)addIntegerParamWithValue:(int)value
{
	[values addObject:[SQLiteQueryParameter integerParameterWithName:nil number:value]];
	return self;
}

- (id)addFloatParamWithValue:(double)value
{
	[values addObject:[SQLiteQueryParameter floatParameterWithName:nil number:value]];
	return self;
}

- (id)addTextParamWithValue:(NSString*)value
{
	[values addObject:[SQLiteQueryParameter textParameterWithName:nil string:value]];
	return self;
}

- (id)addBlobParamWithValue:(NSData*)value
{
	[values addObject:[SQLiteQueryParameter blobParameterWithName:nil data:value]];
	return self;
}

- (id)addNullParam
{
	[values addObject:[SQLiteQueryParameter nullParameterWithName:nil]];
	return self;
}

#pragma mark -
#pragma mark getter functions

- (NSString*)queryString
{
	return query;
}

- (NSArray*)bindArguments
{
	return values;
}

#pragma mark -
#pragma mark etc.

- (void)dealloc
{
	[query release];
	[values release];

	[super dealloc];
}

@end
