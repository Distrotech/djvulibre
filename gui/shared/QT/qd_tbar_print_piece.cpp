//C-  -*- C++ -*-
//C- -------------------------------------------------------------------
//C- DjVuLibre-3.5
//C- Copyright (c) 2002  Leon Bottou and Yann Le Cun.
//C- Copyright (c) 2001  AT&T
//C-
//C- This software is subject to, and may be distributed under, the
//C- GNU General Public License, Version 2. The license should have
//C- accompanied the software or you may obtain a copy of the license
//C- from the Free Software Foundation at http://www.fsf.org .
//C-
//C- This program is distributed in the hope that it will be useful,
//C- but WITHOUT ANY WARRANTY; without even the implied warranty of
//C- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//C- GNU General Public License for more details.
//C- 
//C- DjVuLibre-3.5 is derived from the DjVu(r) Reference Library
//C- distributed by Lizardtech Software.  On July 19th 2002, Lizardtech 
//C- Software authorized us to replace the original DjVu(r) Reference 
//C- Library notice by the following text (see doc/lizard2002.djvu):
//C-
//C-  ------------------------------------------------------------------
//C- | DjVu (r) Reference Library (v. 3.5)
//C- | Copyright (c) 1999-2001 LizardTech, Inc. All Rights Reserved.
//C- | The DjVu Reference Library is protected by U.S. Pat. No.
//C- | 6,058,214 and patents pending.
//C- |
//C- | This software is subject to, and may be distributed under, the
//C- | GNU General Public License, Version 2. The license should have
//C- | accompanied the software or you may obtain a copy of the license
//C- | from the Free Software Foundation at http://www.fsf.org .
//C- |
//C- | The computer code originally released by LizardTech under this
//C- | license and unmodified by other parties is deemed "the LIZARDTECH
//C- | ORIGINAL CODE."  Subject to any third party intellectual property
//C- | claims, LizardTech grants recipient a worldwide, royalty-free, 
//C- | non-exclusive license to make, use, sell, or otherwise dispose of 
//C- | the LIZARDTECH ORIGINAL CODE or of programs derived from the 
//C- | LIZARDTECH ORIGINAL CODE in compliance with the terms of the GNU 
//C- | General Public License.   This grant only confers the right to 
//C- | infringe patent claims underlying the LIZARDTECH ORIGINAL CODE to 
//C- | the extent such infringement is reasonably necessary to enable 
//C- | recipient to make, have made, practice, sell, or otherwise dispose 
//C- | of the LIZARDTECH ORIGINAL CODE (or portions thereof) and not to 
//C- | any greater extent that may be necessary to utilize further 
//C- | modifications or combinations.
//C- |
//C- | The LIZARDTECH ORIGINAL CODE is provided "AS IS" WITHOUT WARRANTY
//C- | OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
//C- | TO ANY WARRANTY OF NON-INFRINGEMENT, OR ANY IMPLIED WARRANTY OF
//C- | MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
//C- +------------------------------------------------------------------
// 
// $Id$
// $Name$

#ifdef __GNUG__
#pragma implementation
#endif
#include "DjVuConfig.h"

#include "qd_tbar_print_piece.h"
#include "debug.h"
#include "qlib.h"
#include "qd_base.h"
#include "qd_toolbutt.h"
#include "djvu_base_res.h"
#include "cin_data.h"



//****************************************************************************
//***************************** QDTBarPrintPiece *****************************
//****************************************************************************

void
QDTBarPrintPiece::setEnabled(bool en)
{
   print_butt->setEnabled(en);
   find_butt->setEnabled(en);
   save_butt->setEnabled(en);
}

QDTBarPrintPiece::QDTBarPrintPiece(QDToolBar * toolbar) : QDTBarPiece(toolbar)
{
   find_butt=new QDToolButton(*CINData::get("ppm_vfind"), true,
			      IDC_SEARCH, toolbar, tr("Find"));
   connect(find_butt, SIGNAL(clicked(void)), this, SIGNAL(sigFind(void)));
   toolbar->addLeftWidget(find_butt);

   print_butt=new QDToolButton(*CINData::get("ppm_vprint"), true,
			       IDC_PRINT, toolbar, tr("Print"));
   connect(print_butt, SIGNAL(clicked(void)), this, SIGNAL(sigPrint(void)));
   toolbar->addLeftWidget(print_butt);

   save_butt=new QDToolButton(*CINData::get("ppm_vsave"), true,
			      IDC_SAVE_DOC, toolbar, tr("Save"));
   connect(save_butt, SIGNAL(clicked(void)), this, SIGNAL(sigSave(void)));
   toolbar->addLeftWidget(save_butt);
   
   toolbar->addPiece(this);
   toolbar->adjustPositions();
}

void
QDTBarPrintPiece::setOptions(int opts)
{
  bool b;
  b = !(opts & QDBase::OverrideFlags::TOOLBAR_NO_PRINT);
  showOrHide(print_butt, b);
  b = !(opts & QDBase::OverrideFlags::TOOLBAR_NO_SAVE);
  showOrHide(save_butt, b);
  b = !(opts & QDBase::OverrideFlags::TOOLBAR_NO_SEARCH);
  showOrHide(find_butt, b);
}
