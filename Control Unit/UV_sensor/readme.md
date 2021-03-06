## UV flow cell

## What does it do?
During a chromatography run the protein of interest is held back on the column until a specific buffer reaches the column and washes the protein off the column – this is referred to as elution. The fraction collector will create a sequential series of samples coming off the column, some of which will contain the protein.  How can we identify which fractions are valuable to us?

Most proteins in solution can not be seen by the naked eye in the visible light spectrum, but a majority absorbs UV light. By shining a constant amount of UV light through the sample and measuring how much UV light exits at the other side of the sample, we can identify fractions that contain the largest amount of protein and therefore absorb the largest amount of UV light This can either be done after the purification is finished, but most modern FPLC systems would constantly monitor these measurements while the sample is separated into fractions.

Proteins that contain amino acids with aromatic rings (Tryptophan, Tyrosine) absorb light at 280 nm (UV). In a photometer, light is filtered down to a specific wavelength or wavelength range, directed through the sample and the transmitted light detected. The resulting signal is dependent on the distance through the sample, the concentration of protein in the sample and the specific absorption coefficient. This relationship is described by the Beer-Lambert Law.

## How is it implemented?

Requirements:
-	small volume in the flow cell to minimize dead volume 
-	280 nm light must not be absorbed by the container
-	pressure proof
-	280 nm light must be contained to ensure safety
-	cheap

Commercial flow cells tend to cost hundreds of pounds. They rely on glass or quartz chambers which are UV permissive, and use strong, wide-band light sources to allow flexible measurements of various wavelengths, to allow flexible detection of various compounds depending on the application. 

We decided to create a cheap flow cell based on disposable plastic cuvettes that are transparent to UV light. They create a 10 mm path length through the sample, but are normally not suited to continuous usage. By designing a custom 3D printed plug, we created a small enclosed chamber around the light path, with two tubes allowing continuous flow into and out of the cuvette. 
Monochromators, which filter out unwanted wavelengths, are similarly complex and expensive. We therefore bought a 12V 280nm UV LED, with a  narrow emission spectrum, and combined it with a cheap wideband UV detector (280-390nm). While this would normally be not desirable, in a closed system the vast majority of the signal will be generated by the 280nm LED.

The 3D printed enclose creates a housing for the plastic cuvette, creates holders for both the LED and the UV detector and allows a tight connection with the plug. Generous use of silicone sealant both avoids leakage of liquids and light outside the desired light path.



