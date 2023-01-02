# SOMs_World_Happiness_Dataset

Self-Organizing Maps (SOMs) are a type of artificial neural network that can be used to project high-dimensional data onto a lower-dimensional space in an organized manner. SOMs are particularly useful for visualizing patterns in data and for clustering similar data points together.

## How SOMs work?

SOMs are trained using an unsupervised learning algorithm called the Kohonen learning rule. The SOM consists of a grid of "neurons", each of which is connected to the input data points through a series of weights. During training, the weights are adjusted so that the neurons in the SOM are able to effectively "represent" the input data.

The training process starts with the initialization of the weights, which are usually set randomly. The input data is then presented to the network, one data point at a time. For each data point, the neuron with the weights most similar to the input is chosen as the "winning" neuron. The weights of the winning neuron, as well as those of its neighbors, are then adjusted to become more similar to the input data point. This process is repeated for multiple iterations, until the weights of the neurons have converged to a stable configuration.

After training, the data points can be projected onto the SOM by finding the neuron with the weights most similar to the data point. This allows the data to be visualized in a two-dimensional space, with similar data points being clustered together.

## About the Dataset

The World Happiness Report is a survey of the state of global happiness and continues to gain global recognition as governments, organizations and civil society increasingly use happiness indicators to make informative decisions. This report reviews the state of happiness in the world and shows how the new science of happiness explains personnel and national variations in happiness.
The report consists of data from 5 years i.e 2015-19 and spans across various countries. The data collected in the report which form our feature space spans across various indicators such as life expectancy, corruption rate, per capita GDP etc and covers over 150 countries. The list of features provided is as follows:
1. Country
2. Region
3. Happiness rank
4. Happiness score
5. Standard error
6. Economy (GDP per capita)
7. Family
8. Health (Life expectancy)
9. Freedom
10. Trust (Government corruption) 11. Generosity
12. Dystopia residual

## Structs

Structs were defined for both the SOM itself that needs to be initialised and trained, along with the data that is being read from the csv file used for the dataset, as with C we are not afforded the ease of use of packages like pandas that aid dataset manipulation in Python. The struct for the SOM itself includes the following fields, with their descriptions as mentioned in the PDF file uploaded.



