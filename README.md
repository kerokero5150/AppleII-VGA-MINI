# A][ VGA MINI Card
My board concept is to provide inexpensive graphics cards to enthusiasts, don't making their own, so I use a lot of SMD parts that people who like soldering their own don't like. We have prepared two types: Purple and Black.
PCBs smaller than 100x100mm can often be made cheaply, so I tried configuring a small board with SMD parts. We are proud that it has excellent cost performance and has a cool and luxurious feel. It's still in the prototyping stage.<BR><BR>
<img src="Pictures/IMG_8926.jpeg" width="520px"><BR><BR>

- Small size within 100x100mm<BR>
- Uses cheap SMD parts, they are as large as possible, by maximizing the 1.27 pitch ICs, solder defects are less likely to occur at the factory.<BR>
- Short size db15 connectors can be used.<BR>
- Used clone Pi Pico boards, black and purple they look good.<BR>
- Equipped with a 3.3V regulator that generates less heat.<BR>
- Fun artwork by Drake.


<img src="Pictures/IMG_8919.jpeg" width="300px"><BR><BR>

## For other information

### Gerber and soldering work

We have [GERBER](Gerber_GH) to make this card, Raspberry Pi Pico board matches with genuine pinouts.　[Here](A2VGA_BLK_BOM.xlsx) is BOM. Gerber's silkscreen has been modified. This is because the artwork is copyrighted by Drake. Furthermore, since we are not only amateur developers but also have to run our own store, we have a CC BY-NC-SA 4.0 license. You can create it for free if you want to use it.<BR><BR>
If SMD soldering is difficult your own, we think another fork of [Briel's version](https://github.com/retrotink/Apple-II-VGA) is easier to assemble. We refer to his version for the circuit configuration of the buffer transceivers.<BR><BR>

### install the firmeware

This project is fork version of markadev's AppleII VGA, You can set it up by following the article [here](https://github.com/markadev/AppleII-VGA/tree/main/pico).<BR><BR>



<img src="Pictures/IMG_8895.jpeg" width="500px"><BR><BR>
It will be sold 50 USD in our store. *Early February 2024<BR>
https://en.infinityproducts.co.jp/shop-1



