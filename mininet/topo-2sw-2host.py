"""Custom topology example

Two directly connected switches plus a host for each switch:

       host --- switch --- switch --- host

       Adding the 'topos' dict with a key/value pair to generate our newly defined
       topology enables one to pass in '--topo=mytopo' from the command line.
       """

from mininet.topo import Topo
import math

class MyTopo( Topo ):
               "Simple topology example."

               def __init__( self ):
                   "Create custom topo."
                   # Initialize topology
                   Topo.__init__( self )

                   # Add hosts and switches
                   leftSwitch = self.addSwitch( 't0' )
                   rightSwitch = self.addSwitch( 't1' )

                   for i in range(1,3):
                       host = self.addHost('h'+str(i))
                       self.addLink(host,leftSwitch)
                       self.addLink(host,rightSwitch)

                   self.addLink(leftSwitch, rightSwitch)

topos = { 'mytopo': ( lambda: MyTopo() ) }
