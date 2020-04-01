N-D assistant mode: an assistant can access the program and choose one or more plants to weed out / move to the bio-labs for research, in case of blight. The program will allow the assistant to:

See the plant clusters in the database, one by one. When the assistant chooses this option, the data of the first plant (species, coded cluster name, age) is displayed, along with its digitized scan.
Choose to weed out / move the plant cluster, in which case the plant cluster is added to the assistant's “to be displaced” list.
Choose not to uproot / move the plant cluster and to continue to the next. In this case, the information corresponding to the next plant cluster is shown and the assistant is again offered the possibility to uproot it or move it. This can continue as long as the assistant wants, as when arriving to the end of the list, if the assistant chooses next, the application will again show the first plant cluster.
See all plant clusters of a given species, having an age less than a given number. If the species is empty, then all plant clusters will be considered. The same options (a, b and c) apply in this case.
See the list of plant clusters selected to be uprooted or moved to the research labs.
The DinamicVector that you created should now use template, now that you have access to them. All commands must take the form:

next
save codedName (e.g. save I129)
list species, age (e.g. list Solanum tuberosum, 2)
mylist