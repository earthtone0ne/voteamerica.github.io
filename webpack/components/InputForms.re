let component = ReasonReact.statelessComponent("InputForms");
let make = _children => {
  /* https://stackoverflow.com/questions/49039433/how-to-add-a-copyright-symbol-in-reason-react-component */
  let hmtlPlusEntity = <span dangerouslySetInnerHTML={{ "__html": "&plus;" }}></span>;
  let hmtlTimesEntity = <span dangerouslySetInnerHTML={{ "__html": "&times;" }}></span>;
  let hmtlAmpEntity = <span dangerouslySetInnerHTML={{ "__html": "&amp;" }}></span>;

  let regexPattern="(^\\d{5}$)|(^\\d{5}-\\d{4}$)";

  let withDataAttributes = (
  ~data, element
  ) => ReasonReact.cloneElement(element, ~props=Obj.magic(Js.Dict.fromList(data)),[||]);

  /* let inputMonth = (typeName, idName) =>{

    let xId = typeName ++ "Month" ++ idName;
    
    let x = withDataAttributes(~data=[("data-field", "month")], <input className="form-input form-input--tiny input--month" type_="number" id=xId placeholder="MM" min="1" max="12" required=true />
    );

    x;
}; */

  let inputDateSection = (fragment, data) =>{

    let x = withDataAttributes(~data=data, fragment
    );

    x;
  };

  let inputId = (typeName, idName, sectionName) => typeName ++ sectionName ++ idName;

  let inputMonth = (typeName, idName) => {  
    let xId = inputId(typeName, idName, "Month");
    
    let f = <input className="form-input form-input--tiny input--month" type_="number" id=xId placeholder="MM" min=1 max="12" required=true />;

    let data = [("data-field", "month")];

    let x = inputDateSection(f, data);

    x;
  };

  let inputDay = (typeName, idName) =>{  
    let xId = inputId(typeName, idName, "Day");

    let f = <input className="form-input form-input--tiny input--day" type_="number" id=xId placeholder="DD" min=1 max="31" required=true />;

    let data = [("data-field", "day")];

    let x = inputDateSection(f, data);

    x;
  };

  let inputYear = (typeName, idName) => {  
    let xId = inputId(typeName, idName, "Year");

    let f = <input className="form-input form-input--tiny input--year" type_="number" placeholder="YYYY" min=2017 required=true />;

    let data = [("data-field", "year")];

    let x = inputDateSection(f, data);

    x;
  };

  let inputTimeStart = (typeName, idName) => {  
    let xName = typeName ++ "TimeStart";
    let xId = inputId(typeName, idName, "TimeStart");
    let xEnd = "#" ++ inputId(typeName, idName, "TimeEnd");

    let f = <input className="form-input input--time-start" type_="time" name=xName id=xId min=6 max="22:00" value="06:00" required=true />;

    let data = [("data-start", xEnd)];

    let x = inputDateSection(f, data);

    x;
  };

  let inputTimeEnd = (typeName, idName) => {  
    let xName = typeName ++ "TimeEnd";
    let xId = inputId(typeName, idName, "TimeEnd");
    let xEnd = "#" ++ inputId(typeName, idName, "TimeStart");

    let f = <input className="form-input input--time-end" type_="time" name=xName id=xId min=6 max="22:00" value="22:00" required=true />;

    let data = [("data-end", xEnd)];

    let x = inputDateSection(f, data);

    x;
  };

  let inputDate = (typeName, idName) =>{  
    let xId = inputId(typeName, idName, "Date");
    let xName = typeName ++ "Date"

    let f = <input type_="hidden" id=xId className="input--date" name=xName />
;
    f;
  };

  let datePickerRow = {
    let typeName = "Rider";
    let rowId = string_of_int(0);
      
    let row = <script type_="text/template" id="available-time-row">
        <li className="available-times__row">
            <div className="form-group calendar-date-block">
                <label htmlFor="{{type}}Date{{id}}">{ReasonReact.string("Date")}</label>
                <input className="form-input input--date" type_="date" name="{{type}}Date" id="{{type}}Date{{id}}" required=true />
                <div className="help-block with-errors"></div>
            </div>
            <div className="form-group text-date-block">
                <label htmlFor="{{type}}Date{{id}}">{ReasonReact.string("Date")}</label>
                {inputMonth(typeName, rowId)}
                {inputDay(typeName, rowId)}
                {inputYear(typeName, rowId)}
                {inputDate(typeName, rowId)}
                <div className="help-block with-errors"></div>
            </div>
            <div className="form-group">
                <label htmlFor={typeName ++ "TimeStart" ++ rowId}>{ReasonReact.string("Start time")}</label>
                {inputTimeStart(typeName, rowId)}
                <div className="help-block with-errors"></div>
            </div>
            <div className="form-group">
                <label htmlFor={typeName ++ "TimeEnd" ++ rowId}>{ReasonReact.string("End time")}</label>
                {inputTimeEnd(typeName, rowId)}
                <div className="help-block with-errors"></div>
            </div>
            <button className="remove-time button--cancel" ariaLabel="Delete time">{hmtlTimesEntity}</button>
        </li>
    </script>

    row;
    };

  {
  ...component,
  render: _self => {
    
    let ulRiderAvailableTimes = withDataAttributes(~data=[("data-type", "Rider")], <ul id="RiderAvailableTimes" className="available-times" />);

    let ulDriverAvailableTimes = withDataAttributes(~data=[("data-type", "Driver")], <ul id="DriverAvailableTimes" className="available-times" />);

    let inputRiderPreferredEmailContact = withDataAttributes(~data=[("data-emailID", "#riderEmail")], <input className="toggleRequiredEmail" type_="checkbox" name="RiderPreferredContact" value="Email" />);

    /*
        <div id="forms" className="forms wrapper offset-top">
        <form id="need-ride" name="needRide" action="{{ api }}/rider" method="post" className="ride-form" ariaHidden=true>
    */

    let mainDivStyle = ReactDOMRe.Style.make(~marginTop ="150px", ());

    <div> {ReasonReact.string("Input Forms")}
    <div style={mainDivStyle}>
        <div id="formsX" className="forms wrapper offset-top">
        <form id="need-ride" name="needRide" action="{{ api }}/rider" method="post" className="ride-form-op" ariaHidden=false>
            <input type_="hidden" name="_redirect" className="redirect" value="{{ cp_site }}/thanks-rider/?type_=rider" />
            <div className="bannerbox">
                <h2 className="bannerbox__title">{ReasonReact.string("I need a ride")}</h2>
                <div className="bannerbox__content">
                    <a className="close-form button--cancel" href="#intro" ariaLabel="Close form" role="button" ariaControls="need-ride">hmtlTimesEntity</a>

                    <p>{ReasonReact.string("Please enter your details in the form below, and our automatic matching algorithm will use this information to try to find you a driver.")}</p>

                    <fieldset className="rider-select-org">
                        <legend>{ReasonReact.string("Choose your organization")}</legend>

                        <p>{ReasonReact.string("Please choose this carefully as otherwise you may be asked to re-enter your details. Check with your organization if you are not sure.")}</p>

                        <div className="form-column">
                            <div className="form-group">
                                <input id="RidingOnBehalfOfOrganization" name="RidingOnBehalfOfOrganization" type_="hidden" value="true" />
                                <label htmlFor="RidingOBOOrganizationName">{ReasonReact.string("Organization name")}</label>
                                <select id="RidingOBOOrganizationName" name="RidingOBOOrganizationName" required=true >
                                    <option value="None">{ReasonReact.string("None")}</option>
                                    <option value="NAACP">{ReasonReact.string("NAACP")}</option>
                                    <option value="AAPD">{ReasonReact.string("AAPD")}</option>
                                    <option value="PPC">{ReasonReact.string("PPC")}</option>
                                    <option value="MDCC">{ReasonReact.string("MDCC")}</option>
                                    <option value="MarchOn">{ReasonReact.string("MarchOn")}</option>
                                    <option value="CenterCG">{ReasonReact.string("CenterCG")}</option>
                                    <option value="PDAction">{ReasonReact.string("PDAction")}</option>
                                    <option value="DailyKos">{ReasonReact.string("DailyKos")}</option>
                                </select>
                            </div>
                          </div>
                    </fieldset>
                    
                    <fieldset className="date-time-pickers">
                        <legend>{ReasonReact.string("Dates and Times Available")}</legend>

                        <p>{ReasonReact.string("On what dates and times would you be available for the ride? Please pick all the time slots that could work for you: This will make it easier for us to match you with a driver. You can pick multiple time slots, on different dates or on the same date.")}</p>
                        ulRiderAvailableTimes
                        <button className="add-time-btn button" ariaControls="RiderAvailableTimes">hmtlPlusEntity{ReasonReact.string(" Add another date / time")}</button>
                        <small>{ReasonReact.string("(Add as many dates and time ranges as you like)")}</small>
                        <input type_="hidden" className="hiddenJSONTimes" name="AvailableRideTimesJSON" />
                    </fieldset>

                    <fieldset>
                        <legend>{ReasonReact.string("Your location details")}</legend>

                        /* 
                                <input type_="text" className="form-input" id="riderCollectionAddress" placeholder="Your pick up address" name="RiderCollectionAddress" onFocus="autocompleteGeolocate()" required=true />

                                <input type_="text" className="form-input" id="riderDestinationAddress" placeholder="Your destination address" name="RiderDestinationAddress" onFocus="autocompleteGeolocate()" required=true />
                                */

                        <div className="form-column">
                            <div className="form-group">
                                <label htmlFor="riderCollectionAddress">{ReasonReact.string("Pick up address")}</label>
                                <input type_="text" className="form-input" id="riderCollectionAddress" placeholder="Your pick up address" name="RiderCollectionAddress" required=true />
                                <div className="help-block with-errors"></div>
                            </div>
                            <div className="form-group">
                                <label htmlFor="rideArea">{ReasonReact.string("Pick up ZIP code")}</label>
                                <input type_="text" className="form-input form-input--medium" pattern=regexPattern id="rideArea" placeholder="Where you can meet the driver" name="RiderCollectionZIP" required=true />
                                <div className="help-block with-errors"></div>
                            </div>
                            <div className="form-group">
                                <label htmlFor="riderDestinationAddress">{ReasonReact.string("Destination address")}</label>
                                <input type_="text" className="form-input" id="riderDestinationAddress" placeholder="Your destination address" name="RiderDestinationAddress" required=true />
                                <div className="help-block with-errors"></div>
                            </div>
                            <div className="form-group">
                                <label htmlFor="rideDestinationZIP">{ReasonReact.string("Destination ZIP code")}</label>
                                <input type_="text" className="form-input form-input--medium" pattern=regexPattern id="rideDestinationZIP" name="RiderDropOffZIP" placeholder="To where do you need a ride?" required=true />
                                <div className="help-block with-errors"></div>
                            </div>
                        </div>

                        <div className="form-column">
                            <div className="form-group polling-place">
                                <label>{ReasonReact.string("Find your polling place")}</label>
                                <div className="help-block">{ReasonReact.string("(Link will open your state’s polling place checker in a new tab.)")}</div>
                                <ul id="location-details" className="state-dropdown state-dropdown--large">
                                    <li>{ReasonReact.string("Loading&hellip;")}</li>
                                </ul>
                            </div>
                        </div>
                    </fieldset>

                    <fieldset>
                        <legend>{ReasonReact.string("Vehicle requirements")}</legend>
                        <div className="form-group">
                            <label htmlFor="rideSeats">{ReasonReact.string("Number of seats required")}</label>
                            <input type_="number" className="form-input form-input--small" id="rideSeats" name="TotalPartySize" min=1 required=true />
                            <div className="help-block with-errors"></div>
                            <small>{ReasonReact.string("Please let us know how many people will need to travel together in the same car. You may take somebody with you as a safety measure.")}</small>
                            <small>{ReasonReact.string("To make it easier for us to match people, we ask that you travel with as few people as possible.")}</small>
                        </div>
                        <div className="form-group checkbox">
                            <label htmlFor="riderIsPowerChairUser">
                                <input type_="checkbox" name="NeedWheelchair" id="riderIsPowerChairUser"/>{ReasonReact.string("I am a powerchair user who needs an adapted van with a lift.")}
                            </label>
                        </div>
                        <div className="form-group checkbox">
                            <label htmlFor="rideReturn">
                                <input type_="checkbox" name="TwoWayTripNeeded" id="rideReturn" /> {ReasonReact.string("I need a two-way trip.")}
                            </label>
                        </div>
                        <div className="form-group form-inline form-inline-other-requirements">
                            <label htmlFor="RiderAccommodationNotes">{ReasonReact.string("Other Requirements")} <i className="optional">{ReasonReact.string("Optional")}</i></label>
                            <textarea className="form-input" id="RiderAccommodationNotes"
                                  placeholder="Please let us know any other requirements you have for your ride..." name="RiderAccommodationNotes" cols=60 rows=6></textarea>
                        </div>
                        <div className="form-inline">
                            <small>{ReasonReact.string("Please let us know of any other accommodation requirements.")}</small>
                            <ul>
                                <li><small>{ReasonReact.string("Service animal")}</small></li>
                                <li><small>{ReasonReact.string("Assistance folding equipment")}</small></li>
                                <li><small>{ReasonReact.string("Assistance entering/ exiting the Vehicle")}</small></li>
                                <li><small>{ReasonReact.string("Child car seat or booster (please include age)")}</small></li>
                                <li><small>{ReasonReact.string("Do not speak English (please include languages)")}</small></li>
                                <li><small>{ReasonReact.string("Other")}</small></li>
                            </ul>
                        </div>
                    </fieldset>

                    <fieldset>
                        <legend>{ReasonReact.string("Your details")}</legend>

                        <div className="form-group">
                            <label htmlFor="riderFirstName">{ReasonReact.string("First name")}</label>
                            <input type_="text" className="form-input" id="riderFirstName" placeholder="Your first name" name="RiderFirstName" required=true />
                            <div className="help-block with-errors"></div>
                        </div>
                        <div className="form-group">
                            <label htmlFor="riderLastName">{ReasonReact.string("Last name")}</label>
                            <input type_="text" className="form-input" id="riderLastName" placeholder="Your last name" name="RiderLastName" required=true />
                            <div className="help-block with-errors"></div>
                        </div>
                        <div className="form-group">
                            <label htmlFor="riderEmail">{ReasonReact.string("Email address")} <i className="optional">{ReasonReact.string("Optional")}</i></label>
                            <input type_="email" className="form-input" id="riderEmail" placeholder="Email" name="RiderEmail" />
                            <div className="help-block with-errors"></div>
                        </div>
                        <div className="form-group">
                            <label htmlFor="riderPhone">{ReasonReact.string("Phone number (cell preferred)")}</label>
                            <input type_="tel" className="form-input" id="riderPhone" placeholder="Phone" name="RiderPhone" required=true />
                            <div className="help-block with-errors"></div>
                        </div>
                        <div className="form-group radio">
                            <p>{ReasonReact.string("Is this a cell phone?")}</p>
                            <label>
                                <input type_="radio" name="riderCell" value="Yes" />{ReasonReact.string("Yes")}
                            </label>
                            <label>
                                <input type_="radio" name="riderCell" value="No" />{ReasonReact.string("No")}
                            </label>
                        </div>
                        <div className="form-group checkbox checkbox--multi">
                            <p>{ReasonReact.string("How would you prefer the driver contacts you?")}</p>
                            <label>
                                {inputRiderPreferredEmailContact} {ReasonReact.string("Email")}
                            </label>
                            <label>
                                <input type_="checkbox" name="RiderPreferredContact" value="Phone" /> {ReasonReact.string("Phone")}
                            </label>
                            <label>
                                <input type_="checkbox" name="RiderPreferredContact" value="SMS" /> {ReasonReact.string("SMS")}
                            </label>
                        </div>
                    </fieldset>

                    <div className="form-group checkbox">
                        <label htmlFor="RiderAgreeTnC">
                            <input type_="checkbox" id="RiderAgreeTnC" name="RiderAgreeTnC" required=true /> {ReasonReact.string("I agree to the")} <a href="terms-conditions/" target="_blank" >{ReasonReact.string("Terms ")}hmtlAmpEntity{ReasonReact.string(" Conditions.")}</a>
                        </label>
                        <small>{ReasonReact.string("I understand that Carpool Vote LLC will share my contact details with the driver if there's a match. (Carpool Vote will not share personal details with anybody else, unless required by law, and will destroy them within three months of election day if you've asked us not to stay in touch.)")}</small>
                        <small>{ReasonReact.string("I understand that Carpool Vote provides introductions between riders and volunteer drivers who have signed up on the platform. I understand that anybody can sign up to drive and Carpool Vote is unable to perform any background checks on people who use the platform. As with any other environment where I meet new people, I will take steps to keep myself and my possessions safe and accept that Carpool Vote cannot be responsible if anything goes wrong.")}</small>
                        <small>{ReasonReact.string("I understand that Carpool Vote cannot guarantee that I will find a ride by using the platform, or that a driver will complete the ride as agreed. In that case, I will keep looking for a ride until I have reached my destination.")}</small>
                        <small>{ReasonReact.string("I understand that this service is open to any driver or rider - no matter what their personal background or beliefs. To help make sure that both the driver and I feel comfortable and safe, I promise that I will not discuss politics during the journey.")}</small>
                    </div>

                    <div className="form-group checkbox">
                        <label htmlFor="inTouchRider">
                            <input type_="checkbox" id="inTouchRider" name="PleaseStayInTouch" checked=true /> {ReasonReact.string("We'd like to keep you updated from time to time about how the project is progressing. Please untick this box if you'd prefer us not to do this.")}
                        </label>
                    </div>
                    <div className="form-group">
                        <button type_="submit" className="button button--large" id="needRideSubmit">{ReasonReact.string("Sign up")}</button>
                        <a className="align-right close-form" href="#intro">{ReasonReact.string("Back")}</a>
                    </div>
                    <p className="panel-footer"><b>{ReasonReact.string("What happens next?")}</b> {ReasonReact.string("Our system will use these details to automatically try to find you a driver. If there is a match, the driver will get in touch to arrange the ride.")}</p>
                </div>
            </div>
        </form>

        <form id="offer-ride" name="offerRide" action="{{ api }}/driver" method="post" className="ride-form-op" ariaHidden=true>
            <input type_="hidden" name="_redirect" className="redirect" value="{{ cp_site }}/thanks-driver/?type_=driver" />
            <div className="bannerbox">
                <h2 className="bannerbox__title">{ReasonReact.string("I can offer a ride")}</h2>
                <div className="bannerbox__content">
                    <a className="close-form button--cancel" href="#intro" ariaLabel="Close form" role="button" ariaControls="offer-ride">hmtlTimesEntity</a>

                    <fieldset className="driver-select-org">
                        <legend>{ReasonReact.string("Choose your organization")}</legend>

                        <p>{ReasonReact.string("Please choose this carefully as otherwise you may be asked to re-enter your details. Check with your organization if you are not sure.")}</p>

                        <div className="form-column">
                            <div className="form-group">
                                <input id="DrivingOnBehalfOfOrganization" name="DrivingOnBehalfOfOrganization" type_="hidden" value="true" />
                                <label htmlFor="DrivingOBOOrganizationName">{ReasonReact.string("Organization name")}</label>
                                <select id="DrivingOBOOrganizationName" name="DrivingOBOOrganizationName" required=true>
                                    <option value="None">{ReasonReact.string("None")}</option>
                                    <option value="NAACP">{ReasonReact.string("NAACP")}</option>
                                    <option value="AAPD">{ReasonReact.string("AAPD")}</option>
                                    <option value="PPC">{ReasonReact.string("PPC")}</option>
                                    <option value="MDCC">{ReasonReact.string("MDCC")}</option>
                                    <option value="MarchOn">{ReasonReact.string("MarchOn")}</option>
                                    <option value="CenterCG">{ReasonReact.string("CenterCG")}</option>
                                    <option value="PDAction">{ReasonReact.string("PDAction")}</option>
                                    <option value="DailyKos">{ReasonReact.string("DailyKos")}</option>
                                </select>  
                            </div>
                        </div>
                    </fieldset>
                        
                    <fieldset className="date-time-pickers">
                        <legend>{ReasonReact.string("What can you offer?")}</legend>

                        <h3>{ReasonReact.string("Dates and times available")}</h3>
                        <p>{ReasonReact.string("On what dates and times would you be a available to give rides? Please pick all the time slots that could work for you: This will make it easier for us to match you with someone who needs a ride. You can pick multiple time slots, on different dates or on the same date.")}</p>
                        ulDriverAvailableTimes                        
                        <button className="add-time-btn button" ariaControls="DriverAvailableTimes">hmtlPlusEntity{ReasonReact.string(" Add another date / time")}</button>
                        <small>{ReasonReact.string("(Add as many dates and time ranges as you like)")}</small>
                        <input type_="hidden" className="hiddenJSONTimes" name="AvailableDriveTimesJSON" />
                    </fieldset>

                    <fieldset>
                        <legend>{ReasonReact.string("Location and vehicle")}</legend>

                        <div className="form-group">
                            <label htmlFor="rideArea">{ReasonReact.string("Driving ZIP code")}</label>
                            <input type_="text" className="form-input form-input--medium" pattern=regexPattern id="offerArea" placeholder="Where can you pick up the rider?" name="DriverCollectionZIP" required=true />
                            <div className="help-block with-errors"></div>
                        </div>
                        <div className="form-group">
                            <p>{ReasonReact.string("I am willing to collect within a")} 
                            <input type_="number" id="offerMiles" name="DriverCollectionRadius" min=0 step=1.0 className="form-input form-input--inline" placeholder="e.g. 10" required=true />
                            {ReasonReact.string("mile radius of this zip code.")}
                            </p>
                            <div className="help-block with-errors"></div>
                        </div>
                        <div className="form-group">
                            <label htmlFor="driverSeats">{ReasonReact.string("Passenger seats available in vehicle")}</label>
                            <input type_="number" min=0 className="form-input form-input--small" id="driverSeats" name="SeatCount" placeholder="e.g. 2" required=true />
                            <div className="help-block with-errors"></div>
                        </div>
                        <div className="form-group checkbox">
                            <label htmlFor="driverWheelchair">
                                <input type_="checkbox" name="DriverCanLoadRiderWithWheelchair" id="driverWheelchair"/> {ReasonReact.string("I have an adapted van with space for a powerchair")}
                            </label>
                        </div>
                        <div className="form-group checkbox">
                            <label htmlFor="offerInsurance">
                                <input type_="checkbox" name="DriverHasInsurance" id="offerInsurance" required=true/> {ReasonReact.string("I confirm the driver has insurance")}
                            </label>
                            <div className="help-block with-errors"></div>
                        </div>
                        <div className="form-group">
                            <label htmlFor="driverLicence">{ReasonReact.string("Vehicle licence plate number")}</label>
                            <input type_="text" className="form-input form-input--medium" id="driverLicence" name="DriverLicenceNumber" required=true />
                            <div className="help-block with-errors"></div>
                        </div>
                    </fieldset>

                    <fieldset>
                        <legend>{ReasonReact.string("Your details")}</legend>

                        <div className="form-group">
                            <label htmlFor="driverFirstName">{ReasonReact.string("First name")}</label>
                            <input type_="text" className="form-input" id="driverFirstName" placeholder="Your first name" name="DriverFirstName" required=true />
                            <div className="help-block with-errors"></div>
                        </div>
                        <div className="form-group">
                            <label htmlFor="driverLastName">{ReasonReact.string("Last name")}</label>
                            <input type_="text" className="form-input" id="driverLastName" placeholder="Your last name" name="DriverLastName" required=true />
                            <div className="help-block with-errors"></div>
                        </div>
                        <div className="form-group">
                            <label htmlFor="driverEmail">{ReasonReact.string("Email address")}</label>
                            <input type_="email" className="form-input" id="driverEmail" placeholder="Email address" name="DriverEmail" required=true />
                            <div className="help-block with-errors"></div>
                        </div>
                        <div className="form-group">
                            <label htmlFor="driverPhone">{ReasonReact.string("Cell phone number")}</label>
                            <input type_="tel" className="form-input" id="driverPhone" placeholder="Phone" name="DriverPhone" required=true />
                            <div className="help-block with-errors"></div>
                        </div>
                        <div className="form-group checkbox checkbox--multi">
                            <p>{ReasonReact.string("Preferred notification method (choose as many as you like)")}</p>
                            <label>
                                <input type_="checkbox" name="DriverPreferredContact" value="Email" /> {ReasonReact.string("Email")}
                            </label>
                            <label>
                                <input type_="checkbox" name="DriverPreferredContact" value="SMS" /> {ReasonReact.string("SMS")}
                            </label>
                        </div>
                    </fieldset>

                    <div className="form-group checkbox">
                        <label htmlFor="DriverAgreeTnC">
                            <input type_="checkbox" id="DriverAgreeTnC" name="DriverAgreeTnC" required=true /> {ReasonReact.string("I agree to the")} <a href="terms-conditions/" target="_blank">{ReasonReact.string("Terms ")}hmtlAmpEntity{ReasonReact.string(" Conditions.")}</a>
                        </label>
                        <small>{ReasonReact.string("I understand that Carpool Vote LLC will share my contact details with the driver if there's a match. (Carpool Vote will not share personal details with anybody else, unless required by law, and will destroy them within three months of election day if you've asked us not to stay in touch.)")}</small>
                        <small>{ReasonReact.string("I understand that Carpool Vote provides introductions between riders and volunteer drivers who have signed up on the platform. I understand that anybody can sign up to drive and Carpool Vote is unable to perform any background checks on people who use the platform. As with any other environment where I meet new people, I will take steps to keep myself and my possessions safe and accept that Carpool Vote LLC cannot be responsible if anything goes wrong.")}</small>
                        <small>{ReasonReact.string("I understand that Carpool Vote cannot guarantee that I will find appropriate matches through the platform, or that any agreed ride will occur. I take full responsibility for any cost related to using the platform.")}</small>
                        <small>{ReasonReact.string("I understand that this service is open to any driver or rider - no matter what their personal background or beliefs. To help make sure that both the driver and I feel comfortable and safe, I promise that I will not discuss politics during the journey.")}</small>
                    </div>
                    <div className="form-group checkbox">
                        <label htmlFor="inTouchDriver">
                            <input type_="checkbox" id="inTouchDriver" name="PleaseStayInTouch" checked=true /> {ReasonReact.string("We'd like to keep you updated from time to time about how the project is progressing. Please untick this box if you'd prefer us not to do this.")}
                        </label>
                    </div>
                    <div className="form-group">
                        <button type_="submit" className="button button--large" id="offerRideSubmit">{ReasonReact.string("Sign up")}</button>
                        <a className="align-right close-form" href="#intro">{ReasonReact.string("Back")}</a>
                    </div>
                    <p className="panel-footer"><b>{ReasonReact.string("What happens next?")}</b> {ReasonReact.string("Our system will use these details to try to find riders. If there is a potential match, we'll send you a notification. If you accept the match, we'll let the rider know that you'll be in touch to arrange the ride.")}</p>
                </div>
            </div>
        </form>
    </div>
    </div>
  </div>},
}};

let default = ReasonReact.wrapReasonForJs(~component, _jsProps => make([||]));