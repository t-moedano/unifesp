# Register Events

# Pre Requisites

* Truffle instaled 
* Web3 instaled
* npm instaled

# Contract 

The contract to register events has two functions:

# Subscribe

Subscribe a contract in the event if the quota is not exceeded. 
params: eventId (the id of the event) | eventQuota (maximum subscribers permitted)
return the id of the event

# Unscribe

Unsubscribe a contract in the event if has been subscribed. 
params: eventId (the id of the event)
return the id of the event 

# TransferSubscription

Transfer the subscription to the given address.
params: addresTrans (the address of the contract to be transfered)
return the id of the event 
