//
//  controller.hpp
//  autd3
//
//  Created by Shun Suzuki on 04/11/2018.
//  Modified by Shun Suzuki on 04 / 11 / 2018.
//
//

#pragma once

#include <codeanalysis\warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include <Eigen/Core>
#include <Eigen/Geometry> 
#pragma warning( pop )

#include "link.hpp"
#include "geometry.hpp"
#include "gain.hpp"
#include "modulation.hpp"

namespace autd {
	class Controller
	{
	public:
		Controller() noexcept(false);
		~Controller() noexcept(false);
		/*!
		 @brief Open device by link type and location.
			The scheme of location is as follows:
			ETHERCAT - <ams net id> or <ipv4 addr>:<ams net id> (ex. 192.168.1.2:192.168.1.3.1.1 ). The ipv4 addr will be extracted from leading 4 octets of ams net id if not specified.
			ETHERNET - ipv4 addr
			USB      - ignored
			SERIAL   - file discriptor
		 */
		void Open(LinkType type, std::string location = "");
		bool isOpen();
		void Close();

		size_t remainingInBuffer();
		GeometryPtr geometry() noexcept;
		void SetGeometry(const GeometryPtr& geometry) noexcept;

		void SetSilentMode(bool silent) noexcept;
		bool silentMode() noexcept;
		void AppendGain(GainPtr gain);
		void AppendGainSync(GainPtr gain);
		void AppendModulation(ModulationPtr modulation);
		void AppendModulationSync(ModulationPtr modulation);
		void AppendLateralGain(GainPtr gain);
		void AppendLateralGain(const std::vector<GainPtr>& gain_list);
		void StartLateralModulation(float freq);
		void FinishLateralModulation();
		void ResetLateralGain();
		void Flush();

	private:
		class impl;
		class lateraltimer;
		std::shared_ptr<impl> _pimpl;
		std::unique_ptr<lateraltimer> _ptimer;
	};
}