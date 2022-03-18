/*
 * Copyright (C) 2015 Jared Boone, ShareBrained Technology, Inc.
 * Copyright (C) 2016 Furrtek
 *
 * This file is part of PortaPack.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __UI_MICTX_H__
#define __UI_MICTX_H__

#include "ui.hpp"
#include "ui_widget.hpp"
#include "ui_navigation.hpp"
#include "ui_receiver.hpp"
#include "transmitter_model.hpp"
#include "tone_key.hpp"
#include "message.hpp"

namespace ui {

class MicTXView : public View {
public:
	MicTXView(NavigationView& nav);
	~MicTXView();

	MicTXView(const MicTXView&) = delete;
	MicTXView(MicTXView&&) = delete;
	MicTXView& operator=(const MicTXView&) = delete;
	MicTXView& operator=(MicTXView&&) = delete;
	
	void focus() override;
	
	// PTT: Enable through KeyEvent (only works with presses), disable by polling :(
	bool on_key(const KeyEvent key) {
		if ((key == KeyEvent::Right) && (!va_enabled)) {
			set_tx(true);
			return true;
		} else
			return false;
	};
	
	std::string title() const override { return "Microphone TX"; };

private:
	static constexpr uint32_t sampling_rate = 1536000U;
	static constexpr uint32_t lcd_frame_duration = (256 * 1000UL) / 60;	// 1 frame @ 60fps in ms .8 fixed point
	
	void update_vumeter();
	void do_timing();
	void set_tx(bool enable);
	//void on_tuning_frequency_changed();
	void on_tx_progress(const bool done);
	void configure_baseband();
	
	bool transmitting { false };
	bool va_enabled { };
	bool rogerbeep_enabled { };
	uint32_t tone_key_index { };
	float mic_gain { 1.0 };
	uint32_t audio_level { 0 };
	uint32_t va_level { };
	uint32_t attack_ms { };
	uint32_t decay_ms { };
	uint32_t attack_timer { 0 };
	uint32_t decay_timer { 0 };
	
	Labels labels {
		{ { 7 * 8, 1 * 8 }, "Mic. gain:", Color::light_grey() },
		{ { 7 * 8, 4 * 8 }, "Frequency:", Color::light_grey() },
		{ { 7 * 8, 6 * 8 }, "Bandwidth:   kHz", Color::light_grey() },
		{ { 9 * 8, 13 * 8 }, "Level:   /255", Color::light_grey() },
		{ { 9 * 8, 15 * 8 }, "Attack:   ms", Color::light_grey() },
		{ { 9 * 8, 17 * 8 }, "Decay:    ms", Color::light_grey() },
		{ { 7 * 8, 21 * 8 }, "Tone key:", Color::light_grey() }
	};
	
	VuMeter vumeter {
		{ 1 * 8, 2 * 8, 5 * 8, 32 * 8 },
		20,
		false
	};
	
	OptionsField options_gain {
		{ 17 * 8, 1 * 8 },
		4,
		{
			{ "x0.5", 5 },
			{ "x1.0", 10 },
			{ "x1.5", 15 },
			{ "x2.0", 20 }
		}
	};
	
	OptionsField field_frequency {
		{ 17 * 8, 4 * 8 },
		79,
{
{"NULL",0	   },
{"100.1",100100000 },
{"100.3",100300000 },
{"100.6",100600000 },
{"101.0",101000000 },
{"101.2",101200000 },
{"101.4",101400000 },
{"101.6",101600000 },
{"101.8",101800000 },
{"102.0",102000000 },
{"102.3",102300000 },
{"102.5",102500000 },
{"102.8",102800000 },
{"103.0",103000000 },
{"103.2",103200000 },
{"103.4",103400000 },
{"103.6",103600000 },
{"103.8",103800000 },
{"104.0",104000000 },
{"104.2",104200000 },
{"104.4",104400000 },
{"104.5",104500000 },
{"104.6",104600000 },
{"104.8",104800000 },
{"105.0",105000000 },
{"105.2",105200000 },
{"105.5",105500000 },
{"105.8",105800000 },
{"106.1",106100000 },
{"106.5",106500000 },
{"106.8",106800000 },
{"107.0",107000000 },
{"107.2",107200000 },
{"107.4",107400000 },
{"107.6",107600000 },
{"107.8",107800000 },
{"108.0",108000000 },
{"87.5",87500000 },
{"87.8",87800000 },
{"88.0",88000000 },
{"88.1",88100000 },
{"88.4",88400000 },
{"88.8",88800000 },
{"89.2",89200000 },
{"89.4",89400000 },
{"89.6",89600000 },
{"90.0",90000000 },
{"90.4",90400000 },
{"90.7",90700000 },
{"91.0",91000000 },
{"91.7",91700000 },
{"92.0",92000000 },
{"92.8",92800000 },
{"92.3",92300000 },
{"93.2",93200000 },
{"93.5",93500000 },
{"93.9",93900000 },
{"94.0",94000000 },
{"94.3",94300000 },
{"94.5",94500000 },
{"95.0",95000000 },
{"95.6",95600000 },
{"95.9",95900000 },
{"96.1",96100000 },
{"96.8",96800000 },
{"97.1",97100000 },
{"97.4",97400000 },
{"97.9",97900000 },
{"98.1",98100000 },
{"98.3",98300000 },
{"98.6",98600000 },
{"98.9",98900000 },
{"99.1",99100000 },
{"99.35",99350000 },
{"99.4",99400000 },
{"99.5",99500000 },
{"99.7",99700000 },
{"99.9",99900000 },
{"NULL",0	 }	
}



	};
	NumberField field_bw {
		{ 17 * 8, 6 * 8 },
		3,
		{ 0, 150 },
		1,
		' '
	};
	
	Checkbox check_va {
		{ 7 * 8, 10 * 8 },
		7,
		"Voice activation",
		false
	};
	
	NumberField field_va_level {
		{ 15 * 8, 13 * 8 },
		3,
		{ 0, 255 },
		2,
		' '
	};
	NumberField field_va_attack {
		{ 16 * 8, 15 * 8 },
		3,
		{ 0, 999 },
		20,
		' '
	};
	NumberField field_va_decay {
		{ 15 * 8, 17 * 8 },
		4,
		{ 0, 9999 },
		100,
		' '
	};
	
	OptionsField options_tone_key {
		{ 7 * 8, 23 * 8 },
		23,
		{ }
	};

	Checkbox check_rogerbeep {
		{ 7 * 8, 26 * 8 },
		10,
		"Roger beep",
		false
	};
	
	Text text_ptt {
		{ 7 * 8, 17 * 16, 16 * 8, 16 },
		"PTT: RIGHT BUTTON"
	};
	
	MessageHandlerRegistration message_handler_lcd_sync {
		Message::ID::DisplayFrameSync,
		[this](const Message* const) {
			this->update_vumeter();
			this->do_timing();
		}
	};
	
	MessageHandlerRegistration message_handler_audio_level {
		Message::ID::AudioLevelReport,
		[this](const Message* const p) {
			const auto message = static_cast<const AudioLevelReportMessage*>(p);
			this->audio_level = message->value;
		}
	};
	
	MessageHandlerRegistration message_handler_tx_progress {
		Message::ID::TXProgress,
		[this](const Message* const p) {
			const auto message = *reinterpret_cast<const TXProgressMessage*>(p);
			this->on_tx_progress(message.done);
		}
	};
};

} /* namespace ui */

#endif/*__UI_MICTX_H__*/


