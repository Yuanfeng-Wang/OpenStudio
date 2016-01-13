/**********************************************************************
 *  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#ifndef MODEL_DISTRICTHEATING_IMPL_HPP
#define MODEL_DISTRICTHEATING_IMPL_HPP

#include "ModelAPI.hpp"
#include "StraightComponent_Impl.hpp"
#include "../utilities/units/Quantity.hpp"

namespace openstudio {
namespace model {

namespace detail {

  /** DistrictHeating_Impl is a StraightComponent_Impl that is the implementation class for DistrictHeating.*/

  class MODEL_API DistrictHeating_Impl : public StraightComponent_Impl {

   public:

    /** @name Constructors and Destructors */
    //@{

    DistrictHeating_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

    DistrictHeating_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                         Model_Impl* model,
                         bool keepHandle);

    DistrictHeating_Impl(const DistrictHeating_Impl& other,
                         Model_Impl* model,
                         bool keepHandle);

    virtual ~DistrictHeating_Impl() {}

    //@}
    /** @name Virtual Methods */
    //@{

    virtual const std::vector<std::string>& outputVariableNames() const override;

    virtual IddObjectType iddObjectType() const override;

    virtual unsigned inletPort() override;

    virtual unsigned outletPort() override;

    //@}
    /** @name Getters */
    //@{

    boost::optional<double> nominalCapacity() const;

    bool isNominalCapacityAutosized() const;

    //@}
    /** @name Setters */
    //@{

    bool setNominalCapacity(boost::optional<double> nominalCapacity);

    void autosizeNominalCapacity();
    
    bool addToNode(Node & node) override;

    //@}
    /** @name Other */
    //@{



    //@}

   protected:

   private:

    REGISTER_LOGGER("openstudio.model.DistrictHeating");

    openstudio::Quantity nominalCapacity_SI() const;

    openstudio::Quantity nominalCapacity_IP() const;

  };

} // detail



} // model

} // openstudio



#endif // MODEL_DISTRICTHEATING_IMPL_HPP



