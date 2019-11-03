pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                echo 'Building..'
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
            }
        }
        stage('Ansible Deploy') {
            steps {
                echo 'Deploying....'
                dir('scripts')
                {
                echo 'Applying execution rigths'
                sh 'chmod +x ./deploy_with_ansible.sh'
                echo 'Calling Ansibles scritps'
                sh './deploy_with_ansible.sh'
                }
                
            }
        }
    }
}
