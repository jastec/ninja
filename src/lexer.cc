/* Generated by re2c 0.13.5 */
// Copyright 2011 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "lexer.h"

#include <stdio.h>

#include "eval_env.h"
#include "util.h"

bool Lexer::Error(const string& message, string* err) {
  // Compute line/column.
  int line = 1;
  const char* context = input_.str_;
  for (const char* p = input_.str_; p < last_token_; ++p) {
    if (*p == '\n') {
      ++line;
      context = p + 1;
    }
  }
  int col = last_token_ ? last_token_ - context : 0;

  char buf[1024];
  snprintf(buf, sizeof(buf), "%s:%d: ", filename_.AsString().c_str(), line);
  *err = buf;
  *err += message + "\n";

  // Add some context to the message.
  const int kTruncateColumn = 72;
  if (col > 0 && col < kTruncateColumn) {
    int len;
    bool truncated = true;
    for (len = 0; len < kTruncateColumn; ++len) {
      if (context[len] == 0 || context[len] == '\n') {
        truncated = false;
        break;
      }
    }
    *err += string(context, len);
    if (truncated)
      *err += "...";
    *err += "\n";
    *err += string(col, ' ');
    *err += "^ near here";
  }

  return false;
}

Lexer::Lexer(const char* input) {
  Start("input", input);
}

void Lexer::Start(StringPiece filename, StringPiece input) {
  filename_ = filename;
  input_ = input;
  ofs_ = input_.str_;
  last_token_ = NULL;
}

const char* Lexer::TokenName(Token t) {
  switch (t) {
  case ERROR:    return "lexing error";
  case BUILD:    return "'build'";
  case COLON:    return "':'";
  case DEFAULT:  return "'default'";
  case EQUALS:   return "'='";
  case IDENT:    return "identifier";
  case INCLUDE:  return "'include'";
  case INDENT:   return "indent";
  case NEWLINE:  return "newline";
  case PIPE2:    return "'||'";
  case PIPE:     return "'|'";
  case RULE:     return "'rule'";
  case SUBNINJA: return "'subninja'";
  case TEOF:     return "eof";
  }
  return NULL;  // not reached
}

const char* Lexer::TokenErrorHint(Token t) {
  switch (t) {
  case ERROR:    return "";
  case BUILD:    return "";
  case COLON:    return " ($ also escapes ':')";
  case DEFAULT:  return "";
  case EQUALS:   return "";
  case IDENT:    return "";
  case INCLUDE:  return "";
  case INDENT:   return "";
  case NEWLINE:  return "";
  case PIPE2:    return "";
  case PIPE:     return "";
  case RULE:     return "";
  case SUBNINJA: return "";
  case TEOF:     return "";
  }
  return "";
}

void Lexer::UnreadToken() {
  ofs_ = last_token_;
}

Lexer::Token Lexer::ReadToken() {
  const char* p = ofs_;
  const char* q;
  const char* start;
  Lexer::Token token;
  for (;;) {
    start = p;
    
{
	unsigned char yych;
	unsigned int yyaccept = 0;
	static const unsigned char yybm[] = {
		  0,  64,  64,  64,  64,  64,  64,  64, 
		 64,  64,   0,  64,  64,  64,  64,  64, 
		 64,  64,  64,  64,  64,  64,  64,  64, 
		 64,  64,  64,  64,  64,  64,  64,  64, 
		192,  64,  64,  64,  64,  64,  64,  64, 
		 64,  64,  64,  64,  64,  96,  96,  64, 
		 96,  96,  96,  96,  96,  96,  96,  96, 
		 96,  96,  64,  64,  64,  64,  64,  64, 
		 64,  96,  96,  96,  96,  96,  96,  96, 
		 96,  96,  96,  96,  96,  96,  96,  96, 
		 96,  96,  96,  96,  96,  96,  96,  96, 
		 96,  96,  96,  64,  64,  64,  64,  96, 
		 64,  96,  96,  96,  96,  96,  96,  96, 
		 96,  96,  96,  96,  96,  96,  96,  96, 
		 96,  96,  96,  96,  96,  96,  96,  96, 
		 96,  96,  96,  64,  64,  64,  64,  64, 
		 64,  64,  64,  64,  64,  64,  64,  64, 
		 64,  64,  64,  64,  64,  64,  64,  64, 
		 64,  64,  64,  64,  64,  64,  64,  64, 
		 64,  64,  64,  64,  64,  64,  64,  64, 
		 64,  64,  64,  64,  64,  64,  64,  64, 
		 64,  64,  64,  64,  64,  64,  64,  64, 
		 64,  64,  64,  64,  64,  64,  64,  64, 
		 64,  64,  64,  64,  64,  64,  64,  64, 
		 64,  64,  64,  64,  64,  64,  64,  64, 
		 64,  64,  64,  64,  64,  64,  64,  64, 
		 64,  64,  64,  64,  64,  64,  64,  64, 
		 64,  64,  64,  64,  64,  64,  64,  64, 
		 64,  64,  64,  64,  64,  64,  64,  64, 
		 64,  64,  64,  64,  64,  64,  64,  64, 
		 64,  64,  64,  64,  64,  64,  64,  64, 
		 64,  64,  64,  64,  64,  64,  64,  64, 
	};

	yych = *p;
	if (yych <= 'Z') {
		if (yych <= ',') {
			if (yych <= 0x1F) {
				if (yych <= 0x00) goto yy21;
				if (yych == '\n') goto yy6;
				goto yy23;
			} else {
				if (yych <= ' ') goto yy2;
				if (yych == '#') goto yy4;
				goto yy23;
			}
		} else {
			if (yych <= ':') {
				if (yych == '/') goto yy23;
				if (yych <= '9') goto yy20;
				goto yy14;
			} else {
				if (yych == '=') goto yy12;
				if (yych <= '@') goto yy23;
				goto yy20;
			}
		}
	} else {
		if (yych <= 'h') {
			if (yych <= 'a') {
				if (yych == '_') goto yy20;
				if (yych <= '`') goto yy23;
				goto yy20;
			} else {
				if (yych <= 'b') goto yy8;
				if (yych == 'd') goto yy11;
				goto yy20;
			}
		} else {
			if (yych <= 's') {
				if (yych <= 'i') goto yy18;
				if (yych <= 'q') goto yy20;
				if (yych <= 'r') goto yy10;
				goto yy19;
			} else {
				if (yych <= 'z') goto yy20;
				if (yych == '|') goto yy16;
				goto yy23;
			}
		}
	}
yy2:
	yyaccept = 0;
	yych = *(q = ++p);
	goto yy65;
yy3:
	{ token = INDENT;   break; }
yy4:
	yyaccept = 1;
	yych = *(q = ++p);
	if (yych >= 0x01) goto yy60;
yy5:
	{ token = ERROR;    break; }
yy6:
	++p;
yy7:
	{ token = NEWLINE;  break; }
yy8:
	++p;
	if ((yych = *p) == 'u') goto yy54;
	goto yy25;
yy9:
	{ token = IDENT;    break; }
yy10:
	yych = *++p;
	if (yych == 'u') goto yy50;
	goto yy25;
yy11:
	yych = *++p;
	if (yych == 'e') goto yy43;
	goto yy25;
yy12:
	++p;
	{ token = EQUALS;   break; }
yy14:
	++p;
	{ token = COLON;    break; }
yy16:
	++p;
	if ((yych = *p) == '|') goto yy41;
	{ token = PIPE;     break; }
yy18:
	yych = *++p;
	if (yych == 'n') goto yy34;
	goto yy25;
yy19:
	yych = *++p;
	if (yych == 'u') goto yy26;
	goto yy25;
yy20:
	yych = *++p;
	goto yy25;
yy21:
	++p;
	{ token = TEOF;     break; }
yy23:
	yych = *++p;
	goto yy5;
yy24:
	++p;
	yych = *p;
yy25:
	if (yybm[0+yych] & 32) {
		goto yy24;
	}
	goto yy9;
yy26:
	yych = *++p;
	if (yych != 'b') goto yy25;
	yych = *++p;
	if (yych != 'n') goto yy25;
	yych = *++p;
	if (yych != 'i') goto yy25;
	yych = *++p;
	if (yych != 'n') goto yy25;
	yych = *++p;
	if (yych != 'j') goto yy25;
	yych = *++p;
	if (yych != 'a') goto yy25;
	++p;
	if (yybm[0+(yych = *p)] & 32) {
		goto yy24;
	}
	{ token = SUBNINJA; break; }
yy34:
	yych = *++p;
	if (yych != 'c') goto yy25;
	yych = *++p;
	if (yych != 'l') goto yy25;
	yych = *++p;
	if (yych != 'u') goto yy25;
	yych = *++p;
	if (yych != 'd') goto yy25;
	yych = *++p;
	if (yych != 'e') goto yy25;
	++p;
	if (yybm[0+(yych = *p)] & 32) {
		goto yy24;
	}
	{ token = INCLUDE;  break; }
yy41:
	++p;
	{ token = PIPE2;    break; }
yy43:
	yych = *++p;
	if (yych != 'f') goto yy25;
	yych = *++p;
	if (yych != 'a') goto yy25;
	yych = *++p;
	if (yych != 'u') goto yy25;
	yych = *++p;
	if (yych != 'l') goto yy25;
	yych = *++p;
	if (yych != 't') goto yy25;
	++p;
	if (yybm[0+(yych = *p)] & 32) {
		goto yy24;
	}
	{ token = DEFAULT;  break; }
yy50:
	yych = *++p;
	if (yych != 'l') goto yy25;
	yych = *++p;
	if (yych != 'e') goto yy25;
	++p;
	if (yybm[0+(yych = *p)] & 32) {
		goto yy24;
	}
	{ token = RULE;     break; }
yy54:
	yych = *++p;
	if (yych != 'i') goto yy25;
	yych = *++p;
	if (yych != 'l') goto yy25;
	yych = *++p;
	if (yych != 'd') goto yy25;
	++p;
	if (yybm[0+(yych = *p)] & 32) {
		goto yy24;
	}
	{ token = BUILD;    break; }
yy59:
	++p;
	yych = *p;
yy60:
	if (yybm[0+yych] & 64) {
		goto yy59;
	}
	if (yych >= 0x01) goto yy62;
	p = q;
	if (yyaccept <= 0) {
		goto yy3;
	} else {
		goto yy5;
	}
yy62:
	++p;
	{ continue; }
yy64:
	yyaccept = 0;
	q = ++p;
	yych = *p;
yy65:
	if (yybm[0+yych] & 128) {
		goto yy64;
	}
	if (yych == '\n') goto yy66;
	if (yych == '#') goto yy59;
	goto yy3;
yy66:
	++p;
	yych = *p;
	goto yy7;
}

  }

  last_token_ = start;
  ofs_ = p;
  if (token != NEWLINE && token != TEOF)
    EatWhitespace();
  return token;
}

bool Lexer::PeekToken(Token token) {
  Token t = ReadToken();
  if (t == token)
    return true;
  UnreadToken();
  return false;
}

void Lexer::EatWhitespace() {
  const char* p = ofs_;
  for (;;) {
    ofs_ = p;
    
{
	unsigned char yych;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		128,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	yych = *p;
	if (yych <= ' ') {
		if (yych <= 0x00) goto yy73;
		if (yych <= 0x1F) goto yy75;
	} else {
		if (yych == '$') goto yy71;
		goto yy75;
	}
	++p;
	yych = *p;
	goto yy79;
yy70:
	{ continue; }
yy71:
	++p;
	if ((yych = *p) == '\n') goto yy76;
yy72:
	{ break; }
yy73:
	++p;
	{ break; }
yy75:
	yych = *++p;
	goto yy72;
yy76:
	++p;
	{ continue; }
yy78:
	++p;
	yych = *p;
yy79:
	if (yybm[0+yych] & 128) {
		goto yy78;
	}
	goto yy70;
}

  }
}

bool Lexer::ReadIdent(string* out) {
  const char* p = ofs_;
  for (;;) {
    const char* start = p;
    
{
	unsigned char yych;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0, 128, 128,   0, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128,   0,   0,   0,   0,   0,   0, 
		  0, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128,   0,   0,   0,   0, 128, 
		  0, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	yych = *p;
	if (yych <= '@') {
		if (yych <= '.') {
			if (yych <= ',') goto yy84;
		} else {
			if (yych <= '/') goto yy84;
			if (yych >= ':') goto yy84;
		}
	} else {
		if (yych <= '_') {
			if (yych <= 'Z') goto yy82;
			if (yych <= '^') goto yy84;
		} else {
			if (yych <= '`') goto yy84;
			if (yych >= '{') goto yy84;
		}
	}
yy82:
	++p;
	yych = *p;
	goto yy87;
yy83:
	{
      out->assign(start, p - start);
      break;
    }
yy84:
	++p;
	{ return false; }
yy86:
	++p;
	yych = *p;
yy87:
	if (yybm[0+yych] & 128) {
		goto yy86;
	}
	goto yy83;
}

  }
  ofs_ = p;
  EatWhitespace();
  return true;
}

bool Lexer::ReadEvalString(EvalString* eval, bool path, string* err) {
  const char* p = ofs_;
  const char* q;
  const char* start;
  for (;;) {
    start = p;
    
{
	unsigned char yych;
	static const unsigned char yybm[] = {
		  0, 128, 128, 128, 128, 128, 128, 128, 
		128, 128,   0, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		 16, 128, 128, 128,   0, 128, 128, 128, 
		128, 128, 128, 128, 128, 224, 160, 128, 
		224, 224, 224, 224, 224, 224, 224, 224, 
		224, 224,   0, 128, 128, 128, 128, 128, 
		128, 224, 224, 224, 224, 224, 224, 224, 
		224, 224, 224, 224, 224, 224, 224, 224, 
		224, 224, 224, 224, 224, 224, 224, 224, 
		224, 224, 224, 128, 128, 128, 128, 224, 
		128, 224, 224, 224, 224, 224, 224, 224, 
		224, 224, 224, 224, 224, 224, 224, 224, 
		224, 224, 224, 224, 224, 224, 224, 224, 
		224, 224, 224, 128,   0, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
	};
	yych = *p;
	if (yych <= '#') {
		if (yych <= '\n') {
			if (yych <= 0x00) goto yy96;
			if (yych >= '\n') goto yy92;
		} else {
			if (yych == ' ') goto yy92;
		}
	} else {
		if (yych <= ':') {
			if (yych <= '$') goto yy94;
			if (yych >= ':') goto yy92;
		} else {
			if (yych == '|') goto yy92;
		}
	}
	++p;
	yych = *p;
	goto yy120;
yy91:
	{
      eval->AddText(StringPiece(start, p - start));
      continue;
    }
yy92:
	++p;
	{
      if (path) {
        p = start;
        break;
      } else {
        if (*start == '\n')
          break;
        eval->AddText(StringPiece(start, 1));
        continue;
      }
    }
yy94:
	++p;
	if ((yych = *p) <= '/') {
		if (yych <= ' ') {
			if (yych == '\n') goto yy109;
			if (yych <= 0x1F) goto yy98;
			goto yy100;
		} else {
			if (yych <= '$') {
				if (yych <= '#') goto yy98;
				goto yy102;
			} else {
				if (yych == '-') goto yy104;
				goto yy98;
			}
		}
	} else {
		if (yych <= '^') {
			if (yych <= ':') {
				if (yych <= '9') goto yy104;
				goto yy106;
			} else {
				if (yych <= '@') goto yy98;
				if (yych <= 'Z') goto yy104;
				goto yy98;
			}
		} else {
			if (yych <= '`') {
				if (yych <= '_') goto yy104;
				goto yy98;
			} else {
				if (yych <= 'z') goto yy104;
				if (yych <= '{') goto yy108;
				goto yy98;
			}
		}
	}
	{
      last_token_ = start;
      return Error("lexing error", err);
    }
yy96:
	++p;
	{
      last_token_ = start;
      return Error("unexpected EOF", err);
    }
yy98:
	++p;
yy99:
	{
      last_token_ = start;
      return Error("bad $-escape (literal $ must be written as $$)", err);
    }
yy100:
	++p;
	{
      eval->AddText(StringPiece(" ", 1));
      continue;
    }
yy102:
	++p;
	{
      eval->AddText(StringPiece("$", 1));
      continue;
    }
yy104:
	++p;
	yych = *p;
	goto yy118;
yy105:
	{
      eval->AddSpecial(StringPiece(start + 1, p - start - 1));
      continue;
    }
yy106:
	++p;
	{
      eval->AddText(StringPiece(":", 1));
      continue;
    }
yy108:
	yych = *(q = ++p);
	if (yybm[0+yych] & 32) {
		goto yy112;
	}
	goto yy99;
yy109:
	++p;
	yych = *p;
	if (yybm[0+yych] & 16) {
		goto yy109;
	}
	{
      continue;
    }
yy112:
	++p;
	yych = *p;
	if (yybm[0+yych] & 32) {
		goto yy112;
	}
	if (yych == '}') goto yy115;
	p = q;
	goto yy99;
yy115:
	++p;
	{
      eval->AddSpecial(StringPiece(start + 2, p - start - 3));
      continue;
    }
yy117:
	++p;
	yych = *p;
yy118:
	if (yybm[0+yych] & 64) {
		goto yy117;
	}
	goto yy105;
yy119:
	++p;
	yych = *p;
yy120:
	if (yybm[0+yych] & 128) {
		goto yy119;
	}
	goto yy91;
}

  }
  last_token_ = start;
  ofs_ = p;
  if (path)
    EatWhitespace();
  // Non-path strings end in newlines, so there's no whitespace to eat.
  return true;
}
