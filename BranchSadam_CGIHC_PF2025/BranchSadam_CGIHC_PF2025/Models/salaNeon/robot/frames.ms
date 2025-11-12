for i = 0 to 100 do (
    sliderTime = i
    print ("Exportando frame " + (i as string))
    exportFile ("C:\\Users\\mrobo\\Desktop\\ProyectoFinal_CompuGrafica\\BranchSadam_CGIHC_PF2025\\BranchSadam_CGIHC_PF2025\\Models\\salaEgipcia\\alien\\frame_" + formattedPrint i format:"03d" + ".obj") #noPrompt selectedOnly:false using:gw_objio
)
