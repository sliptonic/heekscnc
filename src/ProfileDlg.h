// ProfileDlg.h
// Copyright (c) 2010, Dan Heeks
// This program is released under the BSD license. See the file COPYING for details.

class CProfile;
class PictureWindow;
class CLengthCtrl;
class CDoubleCtrl;
class CObjectIdsCtrl;

#include "interface/HDialogs.h"

class ProfileDlg : public HDialog
{
	static wxBitmap* m_general_bitmap;
	static wxBitmap* m_offset_extra_bitmap;
	static wxBitmap* m_outside_bitmap;
	static wxBitmap* m_inside_bitmap;
	static wxBitmap* m_tool_on_line_bitmap;
	static wxBitmap* m_climb_bitmap;
	static wxBitmap* m_conventional_bitmap;
	static wxBitmap* m_roll_bitmap;
	static wxBitmap* m_roll_radius_bitmap;
	static wxBitmap* m_leadlength_bitmap;
	static wxBitmap* m_clearance_height_bitmap;
	static wxBitmap* m_rapid_down_to_bitmap;
	static wxBitmap* m_start_depth_bitmap;
	static wxBitmap* m_final_depth_bitmap;
	static wxBitmap* m_step_down_bitmap;


	CObjectIdsCtrl *m_idsSketches;
	wxComboBox *m_cmbToolOnSide;
	wxComboBox *m_cmbCutMode;
	wxCheckBox *m_chkAutoRollOn;
	wxCheckBox *m_chkAutoRollOff;
	CDoubleCtrl *m_dblRollRadius;
	wxCheckBox *m_chkUseStartPoint;
	wxCheckBox *m_chkUseEndPoint;
	CDoubleCtrl *m_dblExtendBeforeStart;
	CDoubleCtrl *m_dblExtendPastEnd;
	CDoubleCtrl *m_dblLeadInLength;
	CDoubleCtrl *m_dblLeadOutLength;
	CLengthCtrl *m_lgthOffsetExtra;
	wxCheckBox *m_chkDoFinishingPass;
	wxComboBox *m_cmbAbsMode;
	CLengthCtrl *m_lgthClearanceHeight;
	CLengthCtrl *m_lgthRapidDownToHeight;
	CLengthCtrl *m_lgthStartDepth;
	CLengthCtrl *m_lgthFinalDepth;
	CLengthCtrl *m_lgthStepDown;
	CLengthCtrl *m_lgthHFeed;
	CLengthCtrl *m_lgthVFeed;
	CDoubleCtrl *m_dblSpindleSpeed;
	wxTextCtrl *m_txtComment;
	wxCheckBox *m_chkActive;
	wxTextCtrl *m_txtTitle;
	PictureWindow *m_picture;
	wxComboBox *m_cmbTool;



public:
    ProfileDlg(wxWindow *parent, CProfile* object);
	void GetData(CProfile* object);
	void SetFromData(CProfile* object);
	void SetPicture();
	void SetPicture(wxBitmap** bitmap, const wxString& name);

	void OnChildFocus(wxChildFocusEvent& event);
	void OnComboTool(wxCommandEvent& event);

	void OnComboToolOnSide(wxCommandEvent& event);
	void OnComboCutMode(wxCommandEvent& event);
	void OnCheckAutoRollOn(wxCommandEvent& event);
	void OnCheckAutoRollOff(wxCommandEvent& event);
	void OnCheckUseStartPoint(wxCommandEvent& event);
	void OnCheckUseEndPoint(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
};
