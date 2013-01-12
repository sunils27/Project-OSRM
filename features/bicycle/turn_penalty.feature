@routing @bicycle @turn_penalty
Feature: Turn Penalties

	Background:
		Given the profile "bicycle"

	Scenario: Bike - turns should incur a delay, depending on the angle
		Given the node map
		 | h | a | b |
		 | g | x | c |
		 | f | e | d |
		 | z |   |   |

		And the ways
		 | nodes |
		 | xa    |
		 | xb    |
		 | xc    |
		 | xd    |
		 | xe    |
		 | xf    |
		 | xg    |
		 | xh    |
		 | zf    |

		When I route I should get
		 | from | to | route | time    | distance |
		 | e    | f  | xe,xf | 71s +-2 | 242m +-1 |
		 | e    | g  | xe,xg | 51s +-2 | 200m +-1 |
		 | e    | h  | xe,xh | 54s +-2 | 242m +-1 |
		 | e    | a  | xe,xa | 43s +-2 | 200m +-1 |
		 | e    | b  | xe,xb | 53s +-2 | 242m +-1 |
		 | e    | c  | xe,xc | 47s +-2 | 200m +-1 |
		 | e    | d  | xe,xd | 61s +-2 | 242m +-1 |