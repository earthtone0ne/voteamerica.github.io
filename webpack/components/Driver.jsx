import React, { Component } from 'react';
import { connect } from 'react-redux';
import ReactTable from 'react-table';

import 'react-table/react-table.css';

import LeftPaddedButton from './ui/LeftPaddedButton.jsx';

import { DEFAULT_LIST_PAGE_SIZE } from '../actions/types.js';

import {
  getDriversList,
  hideDriversList,
  setInfoDriversList,
  hideExpiredDriversList,
  hideConfirmedDriversList,
  showCurrentDriver,
  hideCurrentDriver
} from '../actions/index.js';

const mapStateToProps = state => {
  const { apiInfo, loginInfo, driversInfo, matchesInfo } = state;

  return { apiInfo, loginInfo, driversInfo, matchesInfo };
};

const mapDispatchToProps = {
  getDriversList,
  hideDriversList,
  setInfoDriversList,
  hideExpiredDriversList,
  hideConfirmedDriversList,
  showCurrentDriver,
  hideCurrentDriver
};

class DriverBase extends Component {
  driversTableOnPageChangeHandler(self) {
    return pageIndex => {
      const { driversInfo, setInfoDriversList } = self.props;

      const { listPageSize } = driversInfo;

      return setInfoDriversList(pageIndex, listPageSize);
    };
  }

  driversTableOnPageChangeSizeHandler(self) {
    return (size, pageIndex) => {
      const { driversInfo, setInfoDriversList } = self.props;

      // const { listPageIndex } = driversInfo;

      return setInfoDriversList(pageIndex, size);
    };
  }

  getTdPropsHandler(self) {
    return (state, rowInfo, column, instance) => {
      const { driversInfo, matchesInfo } = this.props;
      const itemUuid = rowInfo !== undefined ? rowInfo.original.UUID : '';

      const tableClickHandler = (e, handleOriginal) => {
        const { showCurrentDriver, hideCurrentDriver } = self.props;

        console.log('driver click');

        if (rowInfo !== undefined) {
          const UUID = rowInfo.original.UUID;
          const firstName = rowInfo.original.DriverFirstName;
          const lastName = rowInfo.original.DriverLastName;
          const phone = rowInfo.original.DriverPhone;

          showCurrentDriver({
            UUID,
            DriverFirstName: firstName,
            DriverLastName: lastName,
            DriverPhone: phone
          });
        } else {
          hideCurrentDriver({});
        }

        if (handleOriginal) {
          handleOriginal();
        }
      };

      const getRowBkgColour = () => {
        let col = 'none';

        if (itemUuid == matchesInfo.currentMatch.uuid_driver) {
          col = 'violet';
        } else if (itemUuid == driversInfo.currentDriver.UUID) {
          col = 'green';
        }

        return col;
      };

      const getRowTextColour = () => {
        const col =
          itemUuid == driversInfo.currentDriver.UUID ? 'white' : 'black';

        return col;
      };

      const handlerWrapper = {
        onClick: tableClickHandler,
        style: {
          background: getRowBkgColour(),
          color: getRowTextColour()
        }
      };

      return handlerWrapper;
    };
  }

  driversTableHideExpiredHandler(self) {
    return () => {
      const { hideExpiredDriversList } = self.props;

      hideExpiredDriversList();
    };
  }

  driversTableHideConfirmedHandler(self) {
    return () => {
      const { hideConfirmedDriversList } = self.props;

      hideConfirmedDriversList();
    };
  }

  handleGetDriversListClick(self) {
    return () => {
      const { apiInfo, getDriversList, loginInfo } = self.props;
      const token = loginInfo.token || '';

      return getDriversList(apiInfo.apiUrl, token);
    };
  }

  handleHideDriversListClick(self) {
    return () => {
      const { hideDriversList } = self.props;

      return hideDriversList();
    };
  }

  render() {
    const { loginInfo, driversInfo } = this.props;

    const cellBoolToString = row => String(row.value);

    const driverColumns = [
      { Header: 'UUID', accessor: 'UUID' },
      { Header: 'First Name', accessor: 'DriverFirstName' },
      { Header: 'Last Name', accessor: 'DriverLastName' },
      { Header: 'Email', accessor: 'DriverEmail' },
      {
        Header: 'Powerchair',
        accessor: 'DriverCanLoadRiderWithWheelchair',
        Cell: cellBoolToString
      },
      { Header: 'Status', accessor: 'status' },
      { Header: 'Seats', accessor: 'SeatCount' },
      { Header: 'License', accessor: 'DriverLicenseNumber' },
      { Header: 'Phone', accessor: 'DriverPhone' },
      { Header: 'Collection ZIP', accessor: 'DriverCollectionZIP' },
      { Header: 'City', accessor: 'city' },
      { Header: 'State', accessor: 'full_state' },
      { Header: 'Radius', accessor: 'DriverCollectionRadius' },
      { Header: 'Drive Times', accessor: 'AvailableDriveTimesLocal' },
      { Header: 'Status', accessor: 'status' },
      { Header: 'Status Info', accessor: 'status_info' },
      { Header: 'Created', accessor: 'created_ts' },
      { Header: 'Updated', accessor: 'last_updated_ts' },
      { Header: 'Org', accessor: 'uuid_organization' },
      { Header: 'OrgOBO', accessor: 'DrivingOBOOrganizationName' },
      {
        Header: 'Details Visible',
        accessor: 'RidersCanSeeDriverDetails',
        Cell: ({ value }) => String(value)
      },
      {
        Header: 'No Politics',
        accessor: 'DriverWillNotTalkPolitics',
        Cell: ({ value }) => String(value)
      },
      {
        Header: 'Ready To Match',
        accessor: 'ReadyToMatch',
        Cell: ({ value }) => String(value)
      },
      {
        Header: 'Stay In Touch',
        accessor: 'PleaseStayInTouch',
        Cell: ({ value }) => String(value)
      },
      { Header: 'Contact Method', accessor: 'DriverPreferredContact' },
      {
        Header: 'Will Take Care',
        accessor: 'DriverWillTakeCare',
        Cell: ({ value }) => String(value)
      }
    ];

    const driverTableDivStyle = {
      marginTop: 20,
      marginBottom: 10
    };

    const checkboxAreaStyle = { marginTop: '20px', display: 'inline-block' };

    const checkboxLabelStyle = { paddingRight: '40px' };

    const currentDriverInfo = showCurrentDriverDetails => {
      if (!showCurrentDriverDetails) {
        return <div>No driver selected</div>;
      }

      const currentDriver = driversInfo.currentDriver;
      const uriPhone = encodeURI(currentDriver.DriverPhone);
      const selfServiceUrl =
        '../self-service/?type=driver&uuid=' +
        currentDriver.UUID +
        '&code=0&info&phone=' +
        uriPhone;

      return (
        <div>
          <h3>Current Driver Info</h3>
          <div>
            {currentDriver.DriverFirstName + ' ' + currentDriver.DriverLastName}
          </div>
          <div>
            <a href={selfServiceUrl}>Self Service Page</a>
          </div>
        </div>
      );
    };

    const driversAll = driversInfo.drivers;

    const filterExpiredDrivers = drivers => {
      if (driversInfo.hideExpiredCanceled === true) {
        const filterDrivers = driver =>
          driver.status !== 'Expired' && driver.status !== 'Canceled';

        const driversNotExpired = drivers.filter(filterDrivers);

        return driversNotExpired;
      } else {
        return drivers;
      }
    };

    let filterConfirmedDrivers = drivers => {
      if (driversInfo.hideConfirmed === true) {
        let filterDrivers = driver => driver.status !== 'MatchConfirmed';

        let driversNotConfirmed = drivers.filter(filterDrivers);

        return driversNotConfirmed;
      } else {
        return drivers;
      }
    };

    const tableDriversStepOne = filterExpiredDrivers(driversAll);
    const tableDrivers = filterConfirmedDrivers(tableDriversStepOne);

    return (
      <div>
        {loginInfo.loggedIn === true ? (
          <div>
            <h2 className="operator-page-heading">Driver Info</h2>
            <div>
              {driversInfo.showDriversList === false ? (
                <button
                  className="button button--large"
                  id="showGetDriversList"
                  onClick={this.handleGetDriversListClick(this)}
                >
                  Show Drivers List
                </button>
              ) : (
                <div>
                  <div>
                    <button
                      className="button button--large"
                      id="hideDriversListButton"
                      onClick={this.handleHideDriversListClick(this)}
                    >
                      Hide List
                    </button>
                    <LeftPaddedButton
                      className="button button--large"
                      id="refreshDriversList"
                      onClick={this.handleGetDriversListClick(this)}
                    >
                      Refresh List
                    </LeftPaddedButton>
                  </div>
                  {tableDrivers ? (
                    <div>
                      <div>
                        <div
                          className="form-group checkbox"
                          style={checkboxAreaStyle}
                        >
                          <label
                            className=""
                            style={checkboxLabelStyle}
                            htmlFor="hideExpired"
                          >
                            Hide Expired/Cancelled
                          </label>
                          <input
                            className=""
                            type="checkbox"
                            id="hideExpired"
                            checked={driversInfo.hideExpiredCanceled}
                            onChange={this.driversTableHideExpiredHandler(this)}
                          />
                        </div>
                        <div
                          className="form-group checkbox"
                          style={checkboxAreaStyle}
                        >
                          <label
                            className=""
                            style={checkboxLabelStyle}
                            htmlFor="hideConfirmed"
                          >
                            Hide Confirmed
                          </label>
                          <input
                            className=""
                            type="checkbox"
                            id="hideConfirmed"
                            checked={driversInfo.hideConfirmed}
                            onChange={this.driversTableHideConfirmedHandler(
                              this
                            )}
                          />
                        </div>
                      </div>

                      <div style={driverTableDivStyle}>
                        <ReactTable
                          defaultPageSize={DEFAULT_LIST_PAGE_SIZE}
                          pageSize={driversInfo.listPageSize}
                          data={tableDrivers}
                          columns={driverColumns}
                          onPageChange={this.driversTableOnPageChangeHandler(
                            this
                          )}
                          onPageSizeChange={this.driversTableOnPageChangeSizeHandler(
                            this
                          )}
                          getTdProps={this.getTdPropsHandler(this)}
                        />
                      </div>
                      {currentDriverInfo(driversInfo.showCurrentDriverDetails)}
                    </div>
                  ) : (
                    false
                  )}
                </div>
              )}
            </div>
          </div>
        ) : (
          false
        )}
      </div>
    );
  }
}

const Driver = connect(
  mapStateToProps,
  mapDispatchToProps
)(DriverBase);

export default Driver;
