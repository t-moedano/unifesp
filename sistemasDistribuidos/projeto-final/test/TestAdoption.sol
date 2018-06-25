pragma solidity ^0.4.17;

import "truffle/Assert.sol";
import "truffle/DeployedAddresses.sol";
import "../contracts/Adoption.sol";


contract TestAdoption {
    Adoption adoption = Adoption(DeployedAddresses.Adoption());
    // Testing the adopt() function

    function testSubscription() public {
        uint returnedId = adoption.subscribe(2, 10);
        uint expected = 2;

        Assert.equal(returnedId, expected, "event id was not recorded");
    }

    function testUnSubs() public {
        adoption.subscribe(2, 10);
        uint returnedId = adoption.unscribe(2);
        uint expected = 0;

        Assert.equal(returnedId, expected, "event id should be zero.");
    }

    function testTransfer() public {
      adoption.subscribe(2, 10);
      address addr = 0x6806e1a300A8AC4668b89377D3f482206E70E745;
      uint returnedId = adoption.transferSubscription(addr);
      uint expected = 2;
      Assert.equal(returnedId, expected, "Event Id 2 should be passed to the new address");
    }
}
