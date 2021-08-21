// -*- C++ -*-
// $Id: field.h,v 1.47 2002/07/02 22:10:26 t1mpy Exp $

// id3lib: a C++ library for creating and manipulating id3v1/v2 tags
// Copyright 1999, 2000  Scott Thomas Haug

// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Library General Public License as published by
// the Free Software Foundation; either version 2 of the License, or (at your
// option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
// License for more details.
//
// You should have received a copy of the GNU Library General Public License
// along with this library; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

// The id3lib authors encourage improvements and optimisations to be sent to
// the id3lib coordinator.  Please see the README file for details on where to
// send such submissions.  See the AUTHORS file for a list of people who have
// contributed to id3lib.  See the ChangeLog file for a list of changes to
// id3lib.  These files are distributed with id3lib at
// http://download.sourceforge.net/id3lib/

#ifndef _ID3LIB_FIELD_H_
#define _ID3LIB_FIELD_H_

#include "id3/globals.h" //has <stdlib.h> "id3/sized_types.h"

class ID3_Reader;
class ID3_Writer;

/** \class ID3_Field field.h id3/field.h
 ** \brief The representative class of an ID3v2 field.
 **
 ** As a general rule, you need never create an object of this type.  id3lib
 ** uses them internally as part of the id3_frame class.  You must know how to
 ** interact with these objects, though, and that's what this section is about.
 **
 ** The ID3_Field contains many overloaded methods to provide these facilities
 ** for four different data types: integers, ASCII strings, Unicode strings,
 ** and binary data.
 **
 ** An integer field supports the Get(), Set(uint32), and operator=(uint32)
 ** methods.
 **
 ** Both types of strings support the GetNumTextItems() method.
 **
 ** An ASCII string field supports the Get(char*, size_t, size_t)),
 ** Set(const char*), Add(const char*), and operator=(const char*) methods.
 **
 ** A Unicode field also supports Get(unicode_t*, size_t, size_t),
 ** Set(const unicode_t*), Add(const unicode_t*), and
 ** operator=(const unicode_t*).  Without elaborating, the Unicode
 ** methods behave exactly the same as their ASCII counterparts, taking
 ** \c unicode_t pointers in place of \c char pointers.
 **
 ** All strings in id3lib are handled internally as Unicode.  This means that
 ** when you set a field with an ASCII source type, it will be converted and
 ** stored internally as a Unicode string.  id3lib will handle all necessary
 ** conversions when parsing, rendering, and retrieving.  If you set a field as
 ** an ASCII string, then try to read the string into a \c unicode_t buffer,
 ** id3lib will automatically convert the string into Unicode so this will
 ** function as expected.  The same holds true in reverse.  Of course, when
 ** converting from Unicode to ASCII, you will experience problems when the
 ** Unicode string contains characters that don't map to ISO-8859-1.
 **
 ** A binary field supports the Get(uchar*, size_t), Set(const uchar*, size_t),
 ** FromFile(const char*), and ToFile(const char*) methods.  The binary field
 ** holds miscellaneous data that can't easily be described any other way, such
 ** as a JPEG image.
 **
 ** As a general implementation note, you should be prepared to support all
 ** fields in an id3lib frame, even if all fields in the id3lib version of the
 ** frame aren't present in the id3v2 version.  This is because of frames like
 ** the picture frame, which changed slightly from one version of the id3v2
 ** standard to the next (the IMAGEFORMAT format in 2.0 changed to a MIMETYPE
 ** in 3.0).  If you support all id3lib fields in a given frame, id3lib can
 ** generate the correct id3v2 frame for the id3v2 version you wish to support.
 ** Alternatively, just support the fields you know will be used in, say, 3.0
 ** if you only plan to generate 3.0 tags.
 **
 ** @author Dirk Mahoney
 ** @version $Id: field.cpp,v 1.47 2002/11/03 00:41:27 t1mpy Exp $
 ** \sa ID3_Tag
 ** \sa ID3_Frame
 ** \sa ID3_Err
 **/
class ID3_CPP_EXPORT ID3_Field
{
public:
  virtual void Clear() = 0;

  virtual size_t Size() const = 0;
  virtual size_t BinSize() const = 0;
  virtual size_t GetNumTextItems() const = 0;

  // integer field functions
  virtual ID3_Field&    operator= (uint32 val) = 0;
  virtual void          Set(uint32) = 0;
  virtual uint32        Get() const = 0;

  // ASCII string field functions
  virtual ID3_Field&    operator= (const char* s) = 0;
  virtual size_t        Set(const char*) = 0;
  virtual size_t        Get(char*, size_t) const = 0;
  virtual size_t        Get(char*, size_t, size_t) const = 0;
  virtual const char*   GetRawText() const = 0;
  virtual const char*   GetRawTextItem(size_t) const = 0;
  virtual size_t        Add(const char*) = 0;

  // Unicode string field functions
  virtual ID3_Field&    operator= (const unicode_t* s) = 0;
  virtual size_t        Set(const unicode_t*) = 0;
  virtual size_t        Get(unicode_t *buffer, size_t) const = 0;
  virtual size_t        Get(unicode_t *buffer, size_t, size_t) const = 0;
  virtual const unicode_t* GetRawUnicodeText() const = 0;
  virtual const unicode_t* GetRawUnicodeTextItem(size_t) const = 0;
  virtual size_t        Add(const unicode_t*) = 0;

  // binary field functions
  virtual size_t        Set(const uchar*, size_t) = 0;
  virtual size_t        Get(uchar*, size_t) const = 0;
  virtual const uchar*  GetRawBinary() const = 0;
  virtual void          FromFile(const char*) = 0;
  virtual void          ToFile(const char *sInfo) const = 0;
  
  // miscelaneous functions
  virtual ID3_Field&    operator=( const ID3_Field & ) = 0;
  virtual bool          InScope(ID3_V2Spec spec) const = 0;

  virtual ID3_FieldID   GetID() const = 0;
  virtual ID3_FieldType GetType() const = 0;
  virtual bool          SetEncoding(ID3_TextEnc enc) = 0;
  virtual ID3_TextEnc   GetEncoding() const = 0;
  virtual bool          IsEncodable() const = 0;

  virtual void          Render(ID3_Writer&) const = 0;
  virtual bool          Parse(ID3_Reader&) = 0;
  virtual bool          HasChanged() const = 0;

protected:
  virtual ~ID3_Field() { };

  // To prevent public instantiation, the constructor is made protected
  ID3_Field() { };
};

/** \class ID3_FrameInfo field.h id3/field.h
 ** \brief Provides information about the frame and field types supported by id3lib
 **
 ** You normally only need (at most) one instance of the ID3_FrameInfo.  It
 ** has no member data -- only methods which provide information about the
 ** frame types (and their component fields) supported by id3lib as defined
 ** in field.cpp .
 **
 ** Usage is straightforward.  The following function uses ID3_FrameInfo
 ** to display a summary of all the frames known to id3lib:
 ** \code
 **
 ** void ShowKnownFrameInfo {
 **   ID3_FrameInfo myFrameInfo;
 **   for (int cur = ID3FID_NOFRAME+1; cur <= myFrameInfo.MaxFrameID(); cur ++)
 **   {
 **     cout << "Short ID: " << myFrameInfo.ShortName(ID3_FrameID(cur)) <<
 **     " Long ID: " << myFrameInfo.LongName(ID3_FrameID(cur)) <<
 **     " Desription: " << myFrameInfo.Description(ID3_FrameID(cur)) << endl;
 **   }
 ** }
 ** \endcode
 **
 ** Functions are also provided to glean more information about the individual
 ** fields which make up any given frame type.  The following for() loop,
 ** embedded into the previous for() loop would provide a raw look at such
 ** information.  Realize, of course, that the field type is meaningless
 ** when printed.  Only when it is taken in the context of the ID3_FieldType enum
 ** does it take on any meaningful significance.
 **
 ** \code
 **  for (int cur = ID3FID_NOFRAME+1; cur <= fi.MaxFrameID(); cur ++)
 **  {
 **    int numfields = fi.NumFields(ID3_FrameID(cur));
 **
 **    cout << "ID: " << fi.LongName(ID3_FrameID(cur)) <<
 **    " FIELDS: " << numfields << endl;
 **    for(int i=0;i<numfields;i++) {
 **      cout << "TYPE: " << fi.FieldType(ID3_FrameID(cur),i) <<
 **      " SIZE: " << fi.FieldSize(ID3_FrameID(cur),i) <<
 **      " FLAGS: " << fi.FieldFlags(ID3_FrameID(cur),i) << endl;
 **
 **    }
 **
 **    cout << endl;
 **
 **  }
 ** \endcode
 **
 ** @author Cedric Tefft
 ** @version $Id: field.cpp,v 1.47 2002/11/03 00:41:27 t1mpy Exp $
 **/
class ID3_CPP_EXPORT ID3_FrameInfo
{

public:
  ID3_FrameInfo() {};
  ~ID3_FrameInfo() {};
  char *ShortName(ID3_FrameID frameid);
  char *LongName(ID3_FrameID frameid);
  const char *Description(ID3_FrameID frameid);
  int MaxFrameID();
  int NumFields(ID3_FrameID frameid);
  ID3_FieldType FieldType(ID3_FrameID frameid, int fieldnum);
  size_t FieldSize(ID3_FrameID frameid, int fieldnum);
  flags_t FieldFlags(ID3_FrameID frameid, int fieldnum);
};

#endif /* _ID3LIB_FIELD_H_ */

