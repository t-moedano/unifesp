/**
* Class that provides the UI for the dapp application. Reads the JSON file containing
* the information of the events and load in the page.
**/
App = {
  web3Provider: null,
  contracts: {},

  /**
  * Initialization function that starts the provider from web3 and load the content
  * of JSON file.
  **/
  init: function() {

    $.getJSON('../pets.json', function(data) {
      var eventsRow = $('#eventsRow');
      var eventTemplate = $('#eventTemplate');

      for (i = 0; i < data.length; i ++) {
        eventTemplate.find('.panel-title').text(data[i].name);
        eventTemplate.find('img').attr('src', data[i].picture);
        eventTemplate.find('.pet-location').text(data[i].location);
        eventTemplate.find('.btn-sub').attr('data-id', data[i].id);
        eventsRow.append(eventTemplate.html());
      }
    });

    return App.initWeb3();
  },

  /**
  * Function that initalizes the web3 provider. Web3 is a plugin/framework
  * that handles the transactions on the block chain.
  * @constructor
  **/
  initWeb3: function() {

    if (typeof web3 !== 'undefined') {
      App.web3Provider = web3.currentProvider;
    }
    else {
      App.web3Provider = new Web3.providers.HttpProvider('http://localhost:7545');
    }
    web3 = new Web3(App.web3Provider);
    return App.initContract();
  },

  /**
  * Function the initalizes the contract and link with the web provider. Use
  * the TruffleContract library to get an instance of the contract.
  * @constructor
  */
  initContract: function() {
    $.getJSON('Adoption.json', function(data) {
        var EventArtifact = data;
        App.contracts.Adoption = TruffleContract(EventArtifact);
        App.contracts.Adoption.setProvider(App.web3Provider);
    });
    return App.bindEvents();
  },

  /**
  * Function to watch events on te button click and call the right functions.
  **/
  bindEvents: function() {
    $(document).on('click', '.btn-sub', App.subscribe);
    $(document).on('click', '.btn-unsub', App.unscribe);
  },

  /**
  * Subscribe function responsible to save that one account registered for the event.
  * The transaction confirms the registration belongs to the contract.
  **/
  subscribe: function(event) {
    event.preventDefault();

    var eventId = parseInt($(event.target).data('id'));
    var quota = 10;
    var eventInstance;

web3.eth.getAccounts(function(error, accounts) {
  if (error) {
    console.log(error);
  }

  var account = accounts[0];

  App.contracts.Adoption.deployed().then(function(instance) {
    eventInstance = instance;
    return eventInstance.subscribe(eventId, quota, {from: account, value: 1, gas: 1000000});
  }).then(function(result) {
    console.log(result);
  });
});
},

  /**
  * Function that removes the subscription of the contract in the event.
  *
  */
  unscribe: function(event) {
    event.preventDefault();

    var eventId = parseInt($(event.target).data('id'));

    var eventInstance;

web3.eth.getAccounts(function(error, accounts) {
  if (error) {
    console.log(error);
  }

  var account = accounts[0];

  App.contracts.Adoption.deployed().then(function(instance) {
    eventInstance = instance;

    return eventInstance.unscribe(eventId, {from: account, value: 1, gas: 1000000});
  }).then(function(result) {
    console.log('Unregistered');
  }).catch(function(err) {
    console.log(err.message);
  });
});
  }

};

/**
* Initialization function.
*/
$(function() {
  $(window).load(function() {
    App.init();
  });
});
