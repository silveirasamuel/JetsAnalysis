#!/bin/bash
#SBATCH --job-name=CSJets_100M100J_0.4_0.05
#SBATCH -p serial
#SBATCH --time=3-00:00:00
#SBATCH --ntasks=1
#SBATCH --array=1-100
#SBATCH --output=output_1M100J_0.4_0.05_%a.out
#SBATCH --error=errors_1M100J_0.4_0.05_%a.err
#SBATCH --mail-user=samuel.silveira@aluno.ufabc.edu.br
#SBATCH --mail-type=ALL

module add gnu8/8.3.0
module load gnu8/8.3.0
module load root-6.16.00-gcc-8.3.0-ih7ao2c

echo -e "\n## Job iniciado em $(date +'%d-%m-%Y as %T') ###################"

cd $SLURM_SUBMIT_DIR
echo -e "\n## Diretorio de submissao do job: $SLURM_SUBMIT_DIR \n"

srun ./CSAnalysis ggscbar 1000000 0.4 0.05 $SLURM_ARRAY_TASK_ID $SLURM_ARRAY_TASK_MAX

cd OUTPUT/Histograms_Output/
mkdir -p 100000000_0.4_0.05_100
cd ../../

srun root.exe -q "analysisJetsInvariantMass.C(1000000,0.4,0.05,$SLURM_ARRAY_TASK_ID,$SLURM_ARRAY_TASK_MAX)"
srun root.exe -q "analysisJetsQuarksPt.C(1000000,0.4,0.05,$SLURM_ARRAY_TASK_ID,$SLURM_ARRAY_TASK_MAX)"
srun root.exe -q "analysisMatchesCharmJets.C(1000000,0.4,0.05,$SLURM_ARRAY_TASK_ID,$SLURM_ARRAY_TASK_MAX)"

mkdir -p logs_100M_0.4_0.05_100
mv output_1M100J_0.4_0.05_$SLURM_ARRAY_TASK_ID.out logs_100M_0.4_0.05_100/
mv errors_1M100J_0.4_0.05_$SLURM_ARRAY_TASK_ID.err logs_100M_0.4_0.05_100/

cd OUTPUT/Histograms_Output/100000000_0.4_0.05_100
hadd -f 100M_0.4_0.05_JetsInvariantMass.root *JetsInvariantMass.root
hadd -f 100M_0.4_0.05_MatchesJets.root *Jets.root
hadd -f 100M_0.4_0.05_JetsQuarksPt.root *JetsQuarksPt.root

echo -e "\n## Job finalizado em $(date +'%d-%m-%Y as %T') ###################"
           
