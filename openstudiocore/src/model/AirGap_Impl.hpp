/**********************************************************************
 *  Copyright (c) 2008-2014, Alliance for Sustainable Energy.
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

#ifndef MODEL_AIRGAP_IMPL_HPP
#define MODEL_AIRGAP_IMPL_HPP

#include <model/ModelAPI.hpp>
#include <model/OpaqueMaterial_Impl.hpp>

#include <utilities/units/Quantity.hpp>
#include <utilities/units/OSOptionalQuantity.hpp>

namespace openstudio {
namespace model {

namespace detail {

  /** AirGap_Impl is a OpaqueMaterial_Impl that is the implementation class for AirGap.*/
  class MODEL_API AirGap_Impl : public OpaqueMaterial_Impl {
    Q_OBJECT;

    Q_PROPERTY(boost::optional<double> thermalResistance READ thermalResistance WRITE setThermalResistance RESET resetThermalResistance);
    Q_PROPERTY(openstudio::OSOptionalQuantity thermalResistance_SI READ thermalResistance_SI WRITE setThermalResistance RESET resetThermalResistance);
    Q_PROPERTY(openstudio::OSOptionalQuantity thermalResistance_IP READ thermalResistance_IP WRITE setThermalResistance RESET resetThermalResistance);

    // TODO: Add relationships for objects related to this one, but not pointed to by the underlying data.
    //       Such relationships can be generated by the GenerateRelationships.rb script.
   public:
    /** @name Constructors and Destructors */
    //@{

    AirGap_Impl(const IdfObject& idfObject,
                Model_Impl* model,
                bool keepHandle);

    AirGap_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                Model_Impl* model,
                bool keepHandle);

    AirGap_Impl(const AirGap_Impl& other,
                Model_Impl* model,
                bool keepHandle);

    virtual ~AirGap_Impl() {}

    //@}

    /** @name Virtual Methods */
    //@{

    virtual const std::vector<std::string>& outputVariableNames() const;

    virtual IddObjectType iddObjectType() const;

    //@}
    /** @name Getters */
    //@{

    double thermalResistance() const;

    OSOptionalQuantity getThermalResistance(bool returnIP=false) const;

    virtual double thickness() const;

    /** The conductivitiy of the material in W/m*K. Always throws becuase no real thickness, which
     *  is needed for conversion. */
    virtual double thermalConductivity() const;

    /** The conductance of the material in W/m^2*K. Always throws becuase no real thickness, which
     *  is needed for conversion. */
    virtual double thermalConductance() const;

    /** The resistivity of the material in m*K/W. Always throws becuase no real thickness, which
     *  is needed for conversion. */
    virtual double thermalResistivity() const;

    virtual double thermalAbsorptance() const;

    virtual boost::optional<double> thermalReflectance() const;

    virtual double solarAbsorptance() const;

    virtual boost::optional<double> solarReflectance() const;

    virtual double visibleTransmittance() const;

    virtual double visibleAbsorptance() const;

    virtual boost::optional<double> visibleReflectance() const;

    //@}
    /** @name Setters */
    //@{

    bool setThermalResistance(boost::optional<double> thermalResistance);

    bool setThermalResistance(const OSOptionalQuantity& thermalResistance);

    void resetThermalResistance();

    virtual bool setThickness(double value);

    /** Sets the conductivity of the material in W/m*K, if possible. Always returns false. */
    virtual bool setThermalConductivity(double value);

    /** Sets the conductance of the material in W/m^2*K, if possible. */
    virtual bool setThermalConductance(double value);

    /** Sets the resistivity of the material in m*K/W, if possible. */
    virtual bool setThermalResistivity(double value);

    /** Sets the resistance of the material in m^2*K/W, if possible. */
    virtual bool setThermalResistance(double value);

    virtual bool setThermalAbsorptance(double value);

    virtual bool setThermalReflectance(boost::optional<double> value);

    virtual bool setSolarAbsorptance(boost::optional<double> value);

    virtual bool setSolarReflectance(boost::optional<double> value);

    virtual bool setVisibleAbsorptance(boost::optional<double> value);

    virtual bool setVisibleReflectance(boost::optional<double> value);

    //@}
    /** @name Other */
    //@{

    //@}
   protected:
   private:
    REGISTER_LOGGER("openstudio.model.AirGap");

    openstudio::OSOptionalQuantity thermalResistance_SI() const;
    openstudio::OSOptionalQuantity thermalResistance_IP() const;
  };

} // detail

} // model
} // openstudio

#endif // MODEL_AIRGAP_IMPL_HPP

