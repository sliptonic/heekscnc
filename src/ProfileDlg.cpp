// ProfileDlg.cpp
// Copyright (c) 2010, Dan Heeks
// This program is released under the BSD license. See the file COPYING for details.

#include "stdafx.h"
#include "ProfileDlg.h"
#include "interface/PictureFrame.h"
#include "interface/NiceTextCtrl.h"
#include "Profile.h"
#include "CTool.h"


enum
{
    ID_SKETCHES = 100,
	ID_OFFSET_EXTRA,
	ID_TOOL_ON_SIDE,
	ID_CUT_MODE,
	ID_USE_AUTO_ROLL_ON,
	ID_USE_AUTO_ROLL_OFF,
	ID_ROLL_RADIUS,
	ID_USE_START_POINT,
	ID_USE_END_POINT,
	ID_EXTEND_BEFORE_START,
	ID_EXTEND_AFTER_END,
	ID_LEAD_IN_LENGTH,
	ID_LEAD_OUT_LENGTH,
	ID_DO_FINISHING_PASS,
	ID_ABS_MODE,
	ID_CLEARANCE_HEIGHT,
	ID_RAPID_SAFETY_SPACE,
	ID_START_DEPTH,
	ID_FINAL_DEPTH,
	ID_STEP_DOWN,
	ID_HFEED,
	ID_VFEED,
	ID_SPINDLE_SPEED,
	ID_COMMENT,
	ID_ACTIVE,
	ID_TITLE,
	ID_TOOL,
};


BEGIN_EVENT_TABLE(ProfileDlg, HDialog)
    EVT_CHILD_FOCUS(ProfileDlg::OnChildFocus)
    EVT_COMBOBOX(ID_TOOL,ProfileDlg::OnComboTool)
    EVT_COMBOBOX(ID_TOOL_ON_SIDE,ProfileDlg::OnComboToolOnSide)
    EVT_COMBOBOX(ID_CUT_MODE,ProfileDlg::OnComboCutMode)
    EVT_CHECKBOX(ID_USE_AUTO_ROLL_ON,ProfileDlg::OnCheckAutoRollOn)
    EVT_CHECKBOX(ID_USE_AUTO_ROLL_OFF,ProfileDlg::OnCheckAutoRollOff)
    EVT_CHECKBOX(ID_USE_START_POINT,ProfileDlg::OnCheckUseStartPoint)
    EVT_CHECKBOX(ID_USE_END_POINT,ProfileDlg::OnCheckUseEndPoint)
END_EVENT_TABLE()

wxBitmap* ProfileDlg::m_general_bitmap = NULL;
wxBitmap* ProfileDlg::m_offset_extra_bitmap = NULL;
wxBitmap* ProfileDlg::m_outside_bitmap = NULL;
wxBitmap* ProfileDlg::m_inside_bitmap = NULL;
wxBitmap* ProfileDlg::m_tool_on_line_bitmap = NULL;
wxBitmap* ProfileDlg::m_climb_bitmap = NULL;
wxBitmap* ProfileDlg::m_conventional_bitmap = NULL;
wxBitmap* ProfileDlg::m_roll_bitmap = NULL;
wxBitmap* ProfileDlg::m_roll_radius_bitmap = NULL;
wxBitmap* ProfileDlg::m_leadlength_bitmap = NULL;
wxBitmap* ProfileDlg::m_clearance_height_bitmap = NULL;
wxBitmap* ProfileDlg::m_rapid_down_to_bitmap = NULL;
wxBitmap* ProfileDlg::m_start_depth_bitmap = NULL;
wxBitmap* ProfileDlg::m_final_depth_bitmap = NULL;
wxBitmap* ProfileDlg::m_step_down_bitmap = NULL;


static std::vector< std::pair< int, wxString > > tools_for_combo;

ProfileDlg::ProfileDlg(wxWindow *parent, CProfile* object)
             : HDialog(parent, wxID_ANY, wxString(_T("Profile Operation")))
{
	m_ignore_event_functions = true;
    wxBoxSizer *sizerMain = new wxBoxSizer(wxHORIZONTAL);

	// add left sizer
    wxBoxSizer *sizerLeft = new wxBoxSizer(wxVERTICAL);
    sizerMain->Add( sizerLeft, 0, wxALL, control_border );

	// add right sizer
    wxBoxSizer *sizerRight = new wxBoxSizer(wxVERTICAL);
    sizerMain->Add( sizerRight, 0, wxALL, control_border );

	// add picture to right side
	m_picture = new PictureWindow(this, wxSize(300, 200));
	wxBoxSizer *pictureSizer = new wxBoxSizer(wxVERTICAL);
	pictureSizer->Add(m_picture, 1, wxGROW);
    sizerRight->Add( pictureSizer, 0, wxALL, control_border );

	// add some of the controls to the right side
	AddLabelAndControl(sizerRight, _("horizontal feedrate"), m_lgthHFeed = new CLengthCtrl(this, ID_HFEED));
	AddLabelAndControl(sizerRight, _("vertical feedrate"), m_lgthVFeed = new CLengthCtrl(this, ID_VFEED));
	AddLabelAndControl(sizerRight, _("spindle speed"), m_dblSpindleSpeed = new CDoubleCtrl(this, ID_SPINDLE_SPEED));

	AddLabelAndControl(sizerRight, _("comment"), m_txtComment = new wxTextCtrl(this, ID_COMMENT));
	sizerRight->Add( m_chkActive = new wxCheckBox( this, ID_ACTIVE, _("active") ), 0, wxALL, control_border );
	AddLabelAndControl(sizerRight, _("title"), m_txtTitle = new wxTextCtrl(this, ID_TITLE));

	// add OK and Cancel to right side
    wxBoxSizer *sizerOKCancel = MakeOkAndCancel(wxHORIZONTAL);
	sizerRight->Add( sizerOKCancel, 0, wxALL | wxALIGN_RIGHT | wxALIGN_BOTTOM, control_border );

	// add all the controls to the left side
	AddLabelAndControl(sizerLeft, _("sketches"), m_idsSketches = new CObjectIdsCtrl(this, ID_SKETCHES));

	wxString tool_on_side_choices[] = {_("Inside"), _("Outside"), _("On")};
	AddLabelAndControl(sizerLeft, _("Tool on Side"), m_cmbToolOnSide = new wxComboBox(this, ID_TOOL_ON_SIDE, _T(""), wxDefaultPosition, wxDefaultSize, 3, tool_on_side_choices));	

	wxString cut_mode_choices[] = {_("climb"), _("conventional")};
	AddLabelAndControl(sizerLeft, _("Cut Mode"), m_cmbCutMode = new wxComboBox(this, ID_CUT_MODE, _T(""), wxDefaultPosition, wxDefaultSize, 2, cut_mode_choices));

	sizerLeft->Add( m_chkAutoRollOn = new wxCheckBox( this, ID_USE_AUTO_ROLL_ON, _("use auto roll on") ), 0, wxALL, control_border );
	sizerLeft->Add( m_chkAutoRollOff = new wxCheckBox( this, ID_USE_AUTO_ROLL_OFF, _("use auto roll off") ), 0, wxALL, control_border );

	AddLabelAndControl(sizerLeft, _("Roll Radius"), m_dblRollRadius = new CDoubleCtrl(this, ID_ROLL_RADIUS));

	sizerLeft->Add( m_chkUseStartPoint = new wxCheckBox( this, ID_USE_START_POINT, _("use start point") ), 0, wxALL, control_border );
	sizerLeft->Add( m_chkUseEndPoint = new wxCheckBox( this, ID_USE_END_POINT, _("use end point") ), 0, wxALL, control_border );


	AddLabelAndControl(sizerLeft, _("Extend before start"), m_dblExtendBeforeStart = new CDoubleCtrl(this, ID_EXTEND_BEFORE_START));
	AddLabelAndControl(sizerLeft, _("Extend past end"), m_dblExtendPastEnd = new CDoubleCtrl(this, ID_EXTEND_AFTER_END));
	AddLabelAndControl(sizerLeft, _("Lead-In length"), m_dblLeadInLength = new CDoubleCtrl(this, ID_LEAD_IN_LENGTH));
	AddLabelAndControl(sizerLeft, _("Lead-Out length"), m_dblLeadOutLength = new CDoubleCtrl(this, ID_LEAD_OUT_LENGTH));

	AddLabelAndControl(sizerLeft, _("Extra Offset"), m_lgthOffsetExtra = new CLengthCtrl(this, ID_OFFSET_EXTRA));

	sizerLeft->Add( m_chkDoFinishingPass = new wxCheckBox( this, ID_DO_FINISHING_PASS, _("Do Finishing Pass") ), 0, wxALL, control_border );

	tools_for_combo = CTool::FindAllTools();

	wxArrayString tools;
	for(unsigned int i = 0; i<tools_for_combo.size(); i++)tools.Add(tools_for_combo[i].second);
	AddLabelAndControl(sizerLeft, _("Tool"), m_cmbTool = new wxComboBox(this, ID_TOOL, _T(""), wxDefaultPosition, wxDefaultSize, tools));

	wxString abs_mode_choices[] = {_("absolute"), _("incremental")};
	AddLabelAndControl(sizerLeft, _("absolute mode"), m_cmbAbsMode = new wxComboBox(this, ID_ABS_MODE, _T(""), wxDefaultPosition, wxDefaultSize, 2, abs_mode_choices));

	AddLabelAndControl(sizerLeft, _("clearance height"), m_lgthClearanceHeight = new CLengthCtrl(this, ID_CLEARANCE_HEIGHT));
	AddLabelAndControl(sizerLeft, _("rapid safety space"), m_lgthRapidDownToHeight = new CLengthCtrl(this, ID_RAPID_SAFETY_SPACE));
	AddLabelAndControl(sizerLeft, _("start depth"), m_lgthStartDepth = new CLengthCtrl(this, ID_START_DEPTH));
	AddLabelAndControl(sizerLeft, _("final depth"), m_lgthFinalDepth = new CLengthCtrl(this, ID_FINAL_DEPTH));
	AddLabelAndControl(sizerLeft, _("step down"), m_lgthStepDown = new CLengthCtrl(this, ID_STEP_DOWN));

	SetFromData(object);

    SetSizer( sizerMain );
    sizerMain->SetSizeHints(this);
	sizerMain->Fit(this);

    m_idsSketches->SetFocus();

	m_ignore_event_functions = false;

	SetPicture();
}

void ProfileDlg::GetData(CProfile* object)
{
	if(m_ignore_event_functions)return;
	m_ignore_event_functions = true;
	object->m_sketches.clear();
#ifdef OP_SKETCHES_AS_CHILDREN
	m_idsSketches->GetAddChildren(object, SketchType);
#else
	m_idsSketches->GetIDList(object->m_sketches);
#endif


	if ( m_cmbToolOnSide->GetValue().CmpNoCase(_("Outside")) == 0) {
		object->m_profile_params.m_tool_on_side = CProfileParams::eLeftOrOutside;
	}
	else if ( m_cmbToolOnSide->GetValue().CmpNoCase(_("Inside")) == 0) {
		object->m_profile_params.m_tool_on_side = CProfileParams::eRightOrInside;
	}
	else if ( m_cmbToolOnSide->GetValue().CmpNoCase(_("On")) == 0) {
		object->m_profile_params.m_tool_on_side = CProfileParams::eOn;
	}


	if ( m_cmbCutMode->GetValue().CmpNoCase(_("Climb")) == 0) {
		object->m_profile_params.m_cut_mode = CProfileParams::eClimb;
	}
	else if (m_cmbCutMode->GetValue().CmpNoCase(_("Conventional")) == 0) {
		object->m_profile_params.m_cut_mode = CProfileParams::eConventional;
	}
	
	object->m_profile_params.m_auto_roll_on = m_chkAutoRollOn->GetValue();
	object->m_profile_params.m_auto_roll_off = m_chkAutoRollOff->GetValue();
	object->m_profile_params.m_auto_roll_radius = m_dblRollRadius->GetValue();
     	object->m_profile_params.m_lead_in_line_len = m_dblLeadInLength->GetValue();
     	object->m_profile_params.m_lead_out_line_len = m_dblLeadOutLength->GetValue();
     	object->m_profile_params.m_extend_at_start = m_dblExtendBeforeStart->GetValue(); 
     	object->m_profile_params.m_extend_at_end = m_dblExtendPastEnd->GetValue();
	object->m_profile_params.m_offset_extra = m_lgthOffsetExtra->GetValue(); // in mm
	object->m_profile_params.m_do_finishing_pass = m_chkDoFinishingPass->GetValue();

/*
Not sure what to do with these parameters.
	object->m_profile_params.m_roll_on_point[3] = m_XXXXX->GetValue();
	object->m_profile_params.m_roll_off_point[3] = m_XXXXX->GetValue();
	object->m_profile_params.m_start_given = m_XXXXX->GetValue();
	object->m_profile_params.m_end_given = m_XXXXX->GetValue();
	object->m_profile_params.m_start[3] = m_XXXXX->GetValue();
	object->m_profile_params.m_end[3] = m_XXXXX->GetValue();
	object->m_profile_params.m_end_beyond_full_profile = m_XXXXX->GetValue();
	object->m_profile_params.m_only_finishing_pass = m_XXXXX->GetValue(); // don't do roughing pass
	object->m_profile_params.m_finishing_h_feed_rate = m_XXXXX->GetValue();
	object->m_profile_params.m_finishing_cut_mode = m_XXXXX->GetValue();
	object->m_profile_params.m_finishing_step_down = m_XXXXX->GetValue();
*/
	object->m_depth_op_params.m_abs_mode = (m_cmbAbsMode->GetValue().CmpNoCase(_("incremental")) == 0) ? CDepthOpParams::eIncremental : CDepthOpParams::eAbsolute;
	object->m_depth_op_params.ClearanceHeight( m_lgthClearanceHeight->GetValue() );
	object->m_depth_op_params.m_rapid_safety_space = m_lgthRapidDownToHeight->GetValue();
	object->m_depth_op_params.m_start_depth = m_lgthStartDepth->GetValue();
	object->m_depth_op_params.m_final_depth = m_lgthFinalDepth->GetValue();
	object->m_depth_op_params.m_step_down = m_lgthStepDown->GetValue();
	object->m_speed_op_params.m_horizontal_feed_rate = m_lgthHFeed->GetValue();
	object->m_speed_op_params.m_vertical_feed_rate = m_lgthVFeed->GetValue();
	object->m_speed_op_params.m_spindle_speed = m_dblSpindleSpeed->GetValue();
	object->m_comment = m_txtComment->GetValue();
	object->m_active = m_chkActive->GetValue();
	
	// get the tool number
	object->m_tool_number = 0;
	if(m_cmbTool->GetSelection() >= 0)object->m_tool_number = tools_for_combo[m_cmbTool->GetSelection()].first;

	object->m_title = m_txtTitle->GetValue();
	m_ignore_event_functions = false;
}

void ProfileDlg::SetFromData(CProfile* object)
{
	m_ignore_event_functions = true;
#ifdef OP_SKETCHES_AS_CHILDREN
	m_idsSketches->SetFromChildren(object, SketchType);
#else
	m_idsSketches->SetFromIDList(object->m_sketches);
#endif



switch (object->m_profile_params.m_tool_on_side) {
	case CProfileParams::eRightOrInside:
		m_cmbCutMode->SetValue(_("Inside"));
		break;
	case CProfileParams::eLeftOrOutside:
		m_cmbCutMode->SetValue(_("Outside"));
		break;
	case CProfileParams::eOn:
		m_cmbCutMode->SetValue(_("On"));
		break;
	default: ;
	}


switch (object->m_profile_params.m_cut_mode) {
	case CProfileParams::eConventional:
		m_cmbCutMode->SetValue(_("Conventional"));
		break;
	case CProfileParams::eClimb:
		m_cmbCutMode->SetValue(_("Climb"));
		break;
	default: ;
	}

	// set the tool combo to the correct tool
	for(unsigned int i = 0; i < tools_for_combo.size(); i++)if(tools_for_combo[i].first == object->m_tool_number){m_cmbTool->SetSelection(i); break;}


	m_chkAutoRollOn->SetValue(object->m_profile_params.m_auto_roll_on);
	m_chkAutoRollOff->SetValue(object->m_profile_params.m_auto_roll_off);
	m_dblRollRadius->SetValue(object->m_profile_params.m_auto_roll_radius);
	m_dblLeadInLength->SetValue(object->m_profile_params.m_lead_in_line_len);
	m_dblLeadOutLength->SetValue(object->m_profile_params.m_lead_out_line_len);
	m_dblExtendBeforeStart->SetValue(object->m_profile_params.m_extend_at_start);
	m_dblExtendPastEnd->SetValue(object->m_profile_params.m_extend_at_end);
	m_lgthOffsetExtra->SetValue(object->m_profile_params.m_offset_extra); // in mm
	m_chkDoFinishingPass->SetValue(object->m_profile_params.m_do_finishing_pass);

	m_cmbAbsMode->SetValue((object->m_depth_op_params.m_abs_mode == CDepthOpParams::eAbsolute) ? _("absolute") : _("incremental"));
	m_lgthClearanceHeight->SetValue(object->m_depth_op_params.ClearanceHeight());
	m_lgthRapidDownToHeight->SetValue(object->m_depth_op_params.m_rapid_safety_space);
	m_lgthStartDepth->SetValue(object->m_depth_op_params.m_start_depth);
	m_lgthFinalDepth->SetValue(object->m_depth_op_params.m_final_depth);
	m_lgthStepDown->SetValue(object->m_depth_op_params.m_step_down);
	m_lgthHFeed->SetValue(object->m_speed_op_params.m_horizontal_feed_rate);
	m_lgthVFeed->SetValue(object->m_speed_op_params.m_vertical_feed_rate);
	m_dblSpindleSpeed->SetValue(object->m_speed_op_params.m_spindle_speed);
	m_txtComment->SetValue(object->m_comment);
	m_chkActive->SetValue(object->m_active);
	m_txtTitle->SetValue(object->m_title);
	m_ignore_event_functions = false;
}

void ProfileDlg::SetPicture(wxBitmap** bitmap, const wxString& name)
{
	m_picture->SetPicture(bitmap, theApp.GetResFolder() + _T("/bitmaps/profile/") + name + _T(".png"), wxBITMAP_TYPE_PNG);
}

void ProfileDlg::SetPicture()
{
	wxWindow* w = FindFocus();

	if(w == m_cmbToolOnSide)
	{
		if(m_cmbToolOnSide->GetValue() == _("Outside"))SetPicture(&m_outside_bitmap, _T("outside sketch"));
		else if (m_cmbToolOnSide->GetValue() == _("Inside"))SetPicture(&m_inside_bitmap, _T("inside sketch"));
		else SetPicture(&m_tool_on_line_bitmap, _T("on line"));
	}
	else if(w == m_cmbCutMode)
	{
		if(m_cmbCutMode->GetValue() == _("Climb"))SetPicture(&m_climb_bitmap, _T("climb"));
		else SetPicture(&m_conventional_bitmap, _T("conventional"));	
	}
	else if(w == m_dblLeadInLength)SetPicture(&m_leadlength_bitmap, _T("lead in"));
	else if(w == m_dblLeadOutLength)SetPicture(&m_leadlength_bitmap, _T("lead in"));
	else if(w == m_chkAutoRollOn)SetPicture(&m_roll_bitmap, _T("roll"));
	else if(w == m_chkAutoRollOff)SetPicture(&m_roll_bitmap, _T("roll"));
	else if(w == m_dblRollRadius)SetPicture(&m_roll_radius_bitmap, _T("roll radius"));
	else if(w == m_lgthClearanceHeight)SetPicture(&m_clearance_height_bitmap, _T("clearance height"));
	else if(w == m_lgthRapidDownToHeight)SetPicture(&m_rapid_down_to_bitmap, _T("rapid down height"));
	else if(w == m_lgthStartDepth)SetPicture(&m_start_depth_bitmap, _T("start depth"));
	else if(w == m_lgthFinalDepth)SetPicture(&m_final_depth_bitmap, _T("final depth"));
	else if(w == m_lgthStepDown)SetPicture(&m_step_down_bitmap, _T("step down"));
	else SetPicture(&m_general_bitmap, _T("general"));
}

void ProfileDlg::OnChildFocus(wxChildFocusEvent& event)
{
	if(m_ignore_event_functions)return;
	if(event.GetWindow())
	{
		SetPicture();
	}
}

void ProfileDlg::OnComboToolOnSide( wxCommandEvent& event )
{
	if(m_ignore_event_functions)return;
	SetPicture();
}
void ProfileDlg::OnComboCutMode( wxCommandEvent& event )
{
	if(m_ignore_event_functions)return;
	SetPicture();
}
void ProfileDlg::OnCheckAutoRollOn( wxCommandEvent& event )
{
	if(m_ignore_event_functions)return;
	SetPicture();
}
void ProfileDlg::OnCheckAutoRollOff( wxCommandEvent& event )
{
	if(m_ignore_event_functions)return;
	SetPicture();
}
void ProfileDlg::OnCheckUseStartPoint( wxCommandEvent& event )
{
	if(m_ignore_event_functions)return;
	SetPicture();
}
void ProfileDlg::OnCheckUseEndPoint( wxCommandEvent& event )
{
	if(m_ignore_event_functions)return;
	SetPicture();
}





